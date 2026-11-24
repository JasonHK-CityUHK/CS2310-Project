"""Exercise Java-world persistence with a temporary world and real TCP clients."""
import gzip
import json
import os
from pathlib import Path
import select
import signal
import socket
import struct
import subprocess
import sys
import tempfile
import time
import zlib

from persistence_client import Buffer, Client, chunk_state, position, read_varint, text, varint


def string(value):
    encoded = value.encode('utf-8')
    return struct.pack('>H', len(encoded)) + encoded


def tag(kind, name, value):
    return bytes([kind]) + string(name) + value


def compound(*values):
    return b''.join(values) + b'\0'


def named_root(*values):
    return b'\x0a\0\0' + compound(*values)


def create_world(root):
    world = root / 'selected-world'
    region_dir = world / 'dimensions/minecraft/overworld/region'
    region_dir.mkdir(parents=True)
    spawn = compound(tag(8, 'dimension', string('minecraft:overworld')),
                     tag(11, 'pos', struct.pack('>iiii', 3, 8, 8, 8)),
                     tag(5, 'yaw', struct.pack('>f', 0)), tag(5, 'pitch', struct.pack('>f', 0)))
    (world / 'level.dat').write_bytes(gzip.compress(named_root(
        tag(10, 'Data', compound(tag(3, 'DataVersion', struct.pack('>i', 5023)), tag(10, 'spawn', spawn))))))
    regions = {}
    for chunk_z in range(-3, 4):
        for chunk_x in range(-3, 4):
            block_states = compound(tag(9, 'palette', b'\x08' + struct.pack('>i', 1) + string('minecraft:stone')))
            section = compound(tag(1, 'Y', b'\0'), tag(10, 'block_states', block_states))
            payload = named_root(tag(3, 'DataVersion', struct.pack('>i', 5023)),
                                 tag(3, 'xPos', struct.pack('>i', chunk_x)),
                                 tag(3, 'zPos', struct.pack('>i', chunk_z)),
                                 tag(8, 'Status', string('minecraft:full')),
                                 tag(9, 'sections', b'\x0a' + struct.pack('>i', 1) + section))
            compressed = zlib.compress(payload)
            record = struct.pack('>iB', len(compressed) + 1, 2) + compressed
            record += bytes((-len(record)) % 4096)
            key = (chunk_x // 32, chunk_z // 32)
            region = regions.setdefault(key, bytearray(8192))
            offset = len(region) // 4096
            location = ((chunk_x % 32) + 32 * (chunk_z % 32)) * 4
            region[location:location + 4] = struct.pack('>I', (offset << 8) | (len(record) // 4096))
            region.extend(record)
    for (region_x, region_z), data in regions.items():
        (region_dir / f'r.{region_x}.{region_z}.mca').write_bytes(data)
    return world


class RunningServer:
    def __init__(self, executable, root):
        self.executable = str(Path(executable).resolve())
        self.root = Path(root)
        self.process = None

    def __enter__(self):
        with socket.socket() as probe:
            probe.bind(('127.0.0.1', 0))
            self.port = probe.getsockname()[1]
        (self.root / 'server.properties').write_text(
            f'server-ip=127.0.0.1\nserver-port={self.port}\nlevel-name=selected-world\n'
            'view-distance=3\n'
            'motd=Quoted "message" \\u2603\n')
        environment = dict(os.environ, MCSERVER_WORLD_FILE=str(self.root / 'ignored.json'))
        self.process = subprocess.Popen([self.executable], cwd=self.root, env=environment,
                                        stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
        deadline = time.monotonic() + 10
        while True:
            if self.process.poll() is not None:
                raise AssertionError('server did not start: ' + self.process.communicate()[0])
            try:
                with socket.create_connection(('127.0.0.1', self.port), timeout=.1):
                    return self
            except OSError:
                if time.monotonic() >= deadline:
                    self.process.kill()
                    raise AssertionError('server startup timed out: ' + self.process.communicate()[0])
                time.sleep(.02)

    def stop(self, shutdown_signal=signal.SIGTERM):
        self.process.send_signal(shutdown_signal)
        self.output = self.process.communicate(timeout=10)[0]
        return self.process.returncode

    def __exit__(self, *_):
        if self.process.poll() is None:
            try:
                self.stop()
            except subprocess.TimeoutExpired:
                self.process.kill()
                self.process.communicate()


def client(server, name):
    return Client(server.port, name, expected_spawn=(8.5, 8., 8.5), expected_chunks=49)


def assert_status(server):
    with socket.create_connection(('127.0.0.1', server.port), timeout=5) as connection:
        def send(packet_id, body=b''):
            packet = varint(packet_id) + body
            connection.sendall(varint(len(packet)) + packet)

        def read(size):
            result = bytearray()
            while len(result) < size:
                part = connection.recv(size - len(result))
                if not part:
                    raise EOFError('server closed status connection')
                result.extend(part)
            return bytes(result)

        send(0, varint(777) + text('localhost') + struct.pack('>H', server.port) + varint(1))
        send(0)
        packet = Buffer(read(read_varint(read)))
        assert packet.integer() == 0
        assert json.loads(packet.read(packet.integer()))['description']['text'] == 'Quoted "message" \u2603'


def mine(server, point):
    player = client(server, 'SaveTester')
    try:
        player.action(0, point, 1)
        player.expect_update(point, 0)
        player.expect_ack(1)
    finally:
        player.close()


def assert_state(server, point, expected):
    player = client(server, 'ReloadTester')
    try:
        x, y, z = point
        assert chunk_state(player.chunks[x // 16, z // 16], x, z, y=y)[0] == expected
    finally:
        player.close()


def assert_chunk_streaming(server):
    player = Client(server.port, 'StreamingTester', expected_spawn=(8.5, 8., 8.5),
                    expected_chunks=None, auto_ack=False)
    try:
        assert player.view_distance == 3, 'login view distance must match server configuration'
        assert player.chunk_order == [(0, 0)], 'player chunk must be sent first'
        assert not select.select([player.socket], [], [], .2)[0], 'batch sent without acknowledgment'
        assert_status(server)

        player.move(72.5, 8., 8.5)
        centers = []
        unloaded = []
        while len(centers) < 4 or not unloaded:
            packet_id, body = player.receive()
            if packet_id == 0x60:
                coordinates = Buffer(body)
                centers.append((coordinates.integer(), coordinates.integer()))
            elif packet_id == 0x26:
                z, x = struct.unpack('>ii', body)
                unloaded.append((x, z))
            else:
                raise AssertionError(f'unexpected packet before acknowledgment: {packet_id}')
        assert centers[-1] == (4, 0)
        assert unloaded == [(0, 0)]

        player.send(0x0B, struct.pack('>f', 1000.0))
        chunks = []
        started = False
        while True:
            packet_id, body = player.receive()
            if packet_id == 0x0C:
                assert not started
                started = True
            elif packet_id == 0x2E:
                assert started
                chunks.append(struct.unpack('>ii', body[:8]))
            elif packet_id == 0x0B:
                assert started and Buffer(body).integer() == len(chunks)
                break
            else:
                raise AssertionError(f'unexpected packet in chunk batch: {packet_id}')
        assert chunks[0] == (3, 0), 'nearest existing chunk should follow a missing player chunk'
        assert 1 <= len(chunks) <= 16
        assert len(set(chunks)) == len(chunks)
        assert all(1 <= x <= 3 and -3 <= z <= 3 for x, z in chunks)
        assert not select.select([player.socket], [], [], .2)[0], 'second batch was not flow-controlled'
        player.send(0x0B, struct.pack('>f', float('nan')))
        assert player.socket.recv(1) == b'', 'non-finite chunk rate must disconnect'
    finally:
        player.close()
    slow = Client(server.port, 'SlowStreamingTester', expected_chunks=None, auto_ack=False)
    try:
        slow.send(0x0B, struct.pack('>f', 0.0))
        if select.select([slow.socket], [], [], .3)[0]:
            while True:
                packet_id, body = slow.receive()
                if packet_id == 0x0B:
                    slow.send(0x0B, struct.pack('>f', 0.0))
                    break
        assert not select.select([slow.socket], [], [], .3)[0], 'zero rate was not bounded'
    finally:
        slow.close()

    delayed = Client(server.port, 'DelayedBatchTester', expected_chunks=None, auto_ack=False)
    try:
        time.sleep(.26)
        delayed.send(0x0B, struct.pack('>f', 1.0))
        count = 0
        while True:
            packet_id, body = delayed.receive()
            if packet_id == 0x2E:
                count += 1
            elif packet_id == 0x0B:
                assert Buffer(body).integer() == count
                break
        assert count >= 4, 'chunk credit did not accrue while awaiting acknowledgment'
    finally:
        delayed.close()
    assert_status(server)


def assert_incomplete_login_does_not_save_profile(server):
    profile_dir = server.root / 'selected-world/playerdata'
    before = set(profile_dir.glob('*.json'))
    with socket.create_connection(('127.0.0.1', server.port), timeout=5) as connection:
        def send(packet_id, body=b''):
            packet = varint(packet_id) + body
            connection.sendall(varint(len(packet)) + packet)

        send(0, varint(777) + text('localhost') + struct.pack('>H', server.port) + varint(2))
        send(0, text('IncompleteLogin') + bytes(16))
        send(1)
        while connection.recv(4096):
            pass
    assert set(profile_dir.glob('*.json')) == before, 'incomplete login saved a player profile'


def run(executable):
    executable = str(Path(executable).resolve())
    with tempfile.TemporaryDirectory(prefix='mcserver-persistence-') as directory:
        root = Path(directory)
        world = create_world(root)
        region = world / 'dimensions/minecraft/overworld/region/r.0.0.mca'
        first = (8, 8, 8)
        second = (11, 8, 8)
        with RunningServer(executable, root) as server:
            assert_status(server)
            assert_incomplete_login_does_not_save_profile(server)
            assert_chunk_streaming(server)
            player = client(server, 'ProtectedEdit')
            player.action(0, (0, 8, 8), 9)
            player.expect_update((0, 8, 8), 1)
            player.expect_ack(9)
            player.close()
            mine(server, first)
            assert server.stop(signal.SIGINT) == 0, server.output
        with RunningServer(executable, root) as server:
            assert_state(server, first, 0)
            player = client(server, 'Placer')
            player.send(0x42, varint(0) + position(8, 7, 8) + varint(1) +
                        struct.pack('>fff??', .5, 1., .5, False, False) + varint(3))
            player.expect_update(first, 1)
            player.expect_ack(3)
            player.close()
            mine(server, second)
            original = region.read_bytes()
            deadline = time.monotonic() + 10
            while region.read_bytes() == original and time.monotonic() < deadline:
                time.sleep(.05)
            assert region.read_bytes() != original, 'autosave did not write the region'
            server.process.kill()
            server.output = server.process.communicate(timeout=10)[0]
        with RunningServer(executable, root) as server:
            assert_state(server, first, 1)
            assert_state(server, second, 0)
            player = client(server, 'Mover')
            player.move(17.5, 8., 8.5)
            unloaded = 0
            while unloaded < 7:
                packet_id, body = player.receive()
                if packet_id == 0x26:
                    unloaded += 1
                if packet_id == 0x0B:
                    player.send(0x0B, struct.pack('>f', 16.0))
            assert unloaded == 7, 'expected old chunks to unload after movement'
            player.close()
        assert not (root / 'world/flat-world.json').exists()
        assert not (root / 'ignored.json').exists()
        assert not (world / 'dimensions/minecraft/overworld/region/r.0.1.mca').exists()
        print('PASS: selected Java world survives edits, shutdown, autosave, restart, and movement')
        invalid_data = dict(os.environ, MCSERVER_DATA_DIR=str(root / 'missing-runtime-data'))
        result = subprocess.run([executable], cwd=root, env=invalid_data, capture_output=True, text=True, timeout=10)
        assert result.returncode == 1 and 'block report' in result.stderr
        third = (4, 8, 8)
        backup = region.with_suffix('.backup')
        with RunningServer(executable, root) as server:
            mine(server, third)
            original = region.read_bytes()
            region.rename(backup)
            region.mkdir()
            time.sleep(5.5)
            assert backup.read_bytes() == original
            region.rmdir()
            backup.rename(region)
            deadline = time.monotonic() + 10
            while region.read_bytes() == original and time.monotonic() < deadline:
                time.sleep(.05)
            assert region.read_bytes() != original, 'failed save was not retried'
            assert server.stop() == 0
            assert 'cannot save world' in server.output
        with RunningServer(executable, root) as server:
            assert_state(server, third, 0)
        print('PASS: failed region save preserves the snapshot and retries')
        fourth = (4, 8, 11)
        with RunningServer(executable, root) as server:
            mine(server, fourth)
            original = region.read_bytes()
            region.rename(backup)
            region.mkdir()
            assert server.stop() == 1
            assert 'cannot save world' in server.output
        region.rmdir()
        backup.rename(region)
        assert region.read_bytes() == original
        with RunningServer(executable, root) as server:
            assert_state(server, fourth, 1)
        print('PASS: failed final save reports failure and preserves the snapshot')
        level = world / 'level.dat'
        bad = b'not gzip'
        level.write_bytes(bad)
        result = subprocess.run([executable], cwd=root, capture_output=True, text=True, timeout=10)
        assert result.returncode == 1 and 'cannot load world' in result.stderr
        assert level.read_bytes() == bad
        print('PASS: corrupt Java world prevents startup without replacement')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        raise SystemExit('usage: python3 tests/world_persistence_smoke.py path/to/mcserver')
    run(sys.argv[1])
