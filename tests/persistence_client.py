"""Exercise the real server with protocol-777 TCP clients (no game install required).
Run: python3 tests/block_breaking_smoke.py build/src/mcserver
"""
import contextlib
import os
import tempfile
import socket
import struct
import subprocess
import sys
import time


def varint(value):
    result = bytearray()
    value &= 0xFFFFFFFF
    while value > 127:
        result.append((value & 127) | 128)
        value >>= 7
    result.append(value)
    return bytes(result)


def read_varint(read):
    value = 0
    for shift in range(0, 35, 7):
        byte = read(1)[0]
        value |= (byte & 127) << shift
        if not byte & 128:
            return value
    raise AssertionError("malformed VarInt")


def text(value):
    data = value.encode()
    return varint(len(data)) + data


def position(x, y, z):
    return struct.pack('>Q', ((x & 0x3FFFFFF) << 38) | ((z & 0x3FFFFFF) << 12) | (y & 4095))


class Buffer:
    def __init__(self, data):
        self.data = data
        self.cursor = 0

    def read(self, size):
        data = self.data[self.cursor:self.cursor + size]
        assert len(data) == size, 'truncated packet'
        self.cursor += size
        return data

    def integer(self):
        return read_varint(self.read)


class Client:
    def __init__(self, port, name, expected_spawn=None, expected_chunks=9, auto_ack=True):
        self.socket = socket.create_connection(('127.0.0.1', port), timeout=5)
        self.send(0, varint(777) + text('localhost') + struct.pack('>H', port) + varint(2))
        self.expected_spawn = expected_spawn
        self.expected_chunks = expected_chunks
        self.auto_ack = auto_ack
        self.send(0, text(name) + bytes(16))
        assert self.receive()[0] == 2, 'login success'
        self.send(3)
        assert self.receive()[0] == 15, 'known packs'
        self.send(7, varint(0))
        while self.receive()[0] != 3:
            pass
        self.send(3)
        self.chunks = {}
        self.current_position = (.5, 1., .5)
        self.abilities_flags = None
        self.view_distance = None
        self.chunk_order = []
        batch_count = 0
        while True:
            packet_id, body = self.receive()
            if packet_id == 0x32:
                login = Buffer(body)
                login.read(5)
                for _ in range(login.integer()):
                    login.read(login.integer())
                login.integer()
                self.view_distance = login.integer()
            if packet_id == 0x41:
                self.abilities_flags = body[0]
            if packet_id == 0x49:
                spawn = Buffer(body)
                self.teleport_id = spawn.integer()
                self.current_position = struct.unpack('>ddd', spawn.read(24))
            if packet_id == 0x2E:
                chunk = Buffer(body)
                x, z = struct.unpack('>ii', chunk.read(8))
                assert chunk.integer() == 0, 'optional heightmaps'
                self.chunks[x, z] = chunk.read(chunk.integer())
                self.chunk_order.append((x, z))
                batch_count += 1
            if packet_id == 0x0B:
                assert Buffer(body).integer() == batch_count, 'incorrect chunk batch size'
                batch_count = 0
                if self.auto_ack:
                    self.send(0x0B, struct.pack('>f', 16.0))
                if self.expected_chunks is None or len(self.chunks) >= self.expected_chunks:
                    break
        if self.expected_chunks is not None:
            assert len(self.chunks) == self.expected_chunks
        if self.expected_spawn is not None:
            assert self.current_position == self.expected_spawn, 'unexpected world spawn'
        assert self.abilities_flags is not None and not self.abilities_flags & 0x02, \
            'player should not spawn with flight enabled'
        self.send(0, varint(self.teleport_id) + struct.pack('>dddff', *self.current_position, 0., 0.))

    def read(self, size):
        data = bytearray()
        while len(data) < size:
            part = self.socket.recv(size - len(data))
            if not part:
                raise EOFError('server closed connection')
            data.extend(part)
        return bytes(data)

    def receive(self):
        length = read_varint(self.read)
        packet = Buffer(self.read(length))
        return packet.integer(), packet.data[packet.cursor:]

    def send(self, packet_id, body=b''):
        payload = varint(packet_id) + body
        self.socket.sendall(varint(len(payload)) + payload)

    def move(self, x, y, z):
        start = self.current_position
        distance = sum((end - begin) ** 2 for begin, end in zip(start, (x, y, z))) ** .5
        steps = max(1, int(distance / 8) + 1)
        for index in range(1, steps + 1):
            point = [begin + (end - begin) * index / steps for begin, end in zip(start, (x, y, z))]
            self.send(0x1E, struct.pack('>dddB', *point, 1))
        self.current_position = (x, y, z)

    def action(self, action, point, sequence, face=1):
        self.send(0x29, varint(action) + position(*point) + struct.pack('b', face) + varint(sequence))

    def expect_update(self, point, state):
        assert self.receive() == (8, position(*point) + varint(state)), 'block update'

    def expect_ack(self, sequence):
        assert self.receive() == (4, varint(sequence)), 'sequence acknowledgement'

    def close(self):
        self.socket.close()


def chunk_state(data, x, z, y=0):
    chunk = Buffer(data)
    result = None
    for section in range(24):
        blocks, fluid = struct.unpack('>hh', chunk.read(4))
        assert 0 <= fluid <= 4096
        bits = chunk.read(1)[0]
        if bits == 0:
            value = chunk.integer()
        else:
            palette = [chunk.integer() for _ in range(chunk.integer())] if bits <= 8 else None
            per_word = 64 // bits
            word_count = (4096 + per_word - 1) // per_word
            words = struct.unpack('>' + str(word_count) + 'Q', chunk.read(word_count * 8))
            entry = (y % 16) * 256 + (z % 16) * 16 + (x % 16)
            local = (words[entry // per_word] >> ((entry % per_word) * bits)) & ((1 << bits) - 1)
            value = palette[local] if palette is not None else local
        if section == (y + 64) // 16:
            result = (value, blocks)
        biome_bits = chunk.read(1)[0]
        if biome_bits == 0:
            chunk.integer()
        else:
            if biome_bits <= 3:
                for _ in range(chunk.integer()):
                    chunk.integer()
            biome_per_word = 64 // biome_bits
            biome_words = (64 + biome_per_word - 1) // biome_per_word
            chunk.read(biome_words * 8)
    assert chunk.cursor == len(data)
    return result
