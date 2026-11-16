"""Compare a real 26.3 world with packets from the C++ server. Source files stay read-only.
Usage: python3 tests/anvil_import_smoke.py build/src/mcserver /path/to/copied/world
"""
from pathlib import Path
import gzip
import hashlib
import json
import math
import os
import struct
import sys
import tempfile
import zlib

from persistence_client import Buffer, Client
from world_persistence_smoke import RunningServer


class DiskNbt:
    """Independent reference decoder used only to verify real-world test fixtures."""
    def __init__(self, data):
        self.data, self.cursor = data, 0

    def read(self, count):
        value = self.data[self.cursor:self.cursor + count]
        assert count >= 0 and len(value) == count, 'truncated reference NBT'
        self.cursor += count
        return value

    def number(self, kind):
        return struct.unpack('>' + kind, self.read(struct.calcsize('>' + kind)))[0]

    def string(self):
        return self.read(self.number('H')).decode('utf-8')

    def tag(self, kind):
        if kind in (1, 2, 3, 4, 5, 6):
            return self.number({1: 'b', 2: 'h', 3: 'i', 4: 'q', 5: 'f', 6: 'd'}[kind])
        if kind == 7:
            return self.read(self.number('i'))
        if kind == 8:
            return self.string()
        if kind == 9:
            entry, count = self.number('B'), self.number('i')
            assert 0 <= count <= 1000000
            return [self.tag(entry) for _ in range(count)]
        if kind == 10:
            values = {}
            while True:
                entry = self.number('B')
                if entry == 0:
                    return values
                key = self.string()
                values[key] = self.tag(entry)
        if kind in (11, 12):
            count = self.number('i')
            assert 0 <= count <= 1000000
            return [self.number('i' if kind == 11 else 'q') for _ in range(count)]
        raise AssertionError('unknown NBT type')

    def root(self):
        kind = self.number('B')
        self.string()
        return self.tag(kind)


def source_hashes(directory):
    return {str(p.relative_to(directory)): hashlib.sha256(p.read_bytes()).hexdigest()
            for p in directory.rglob('*') if p.is_file()}


def disk_chunk(directory, x, z):
    region = directory / 'dimensions/minecraft/overworld/region' / f'r.{x // 32}.{z // 32}.mca'
    with region.open('rb') as file:
        file.seek(((x % 32) + (z % 32) * 32) * 4)
        location = int.from_bytes(file.read(4), 'big')
        file.seek((location >> 8) * 4096)
        length = int.from_bytes(file.read(4), 'big')
        compression = file.read(1)[0]
        payload = file.read(length - 1)
    assert compression in (1, 2, 3)
    raw = gzip.decompress(payload) if compression == 1 else zlib.decompress(payload) if compression == 2 else payload
    return DiskNbt(raw).root()


def unpack_disk(container, palette, count, minimum):
    if len(palette) == 1:
        return [palette[0]] * count
    bits = max(minimum, (len(palette) - 1).bit_length())
    per_word = 64 // bits
    data = container['data']
    return [palette[((data[i // per_word] & ((1 << 64) - 1)) >> ((i % per_word) * bits)) & ((1 << bits) - 1)]
            for i in range(count)]


def network_container(reader, count, max_local):
    bits = reader.read(1)[0]
    if bits == 0:
        return [reader.integer()] * count
    palette = [reader.integer() for _ in range(reader.integer())] if bits <= max_local else None
    per_word = 64 // bits
    words = struct.unpack('>' + str((count + per_word - 1) // per_word) + 'Q',
                          reader.read(((count + per_word - 1) // per_word) * 8))
    values = [(words[i // per_word] >> ((i % per_word) * bits)) & ((1 << bits) - 1) for i in range(count)]
    return [palette[i] for i in values] if palette is not None else values


def network_chunk(raw):
    reader = Buffer(raw)
    result = []
    for _ in range(24):
        count, fluid = struct.unpack('>hh', reader.read(4))
        blocks = network_container(reader, 4096, 8)
        biomes = network_container(reader, 64, 3)
        result.append((count, fluid, blocks, biomes))
    assert reader.cursor == len(raw)
    return result


def run(executable, directory):
    executable, directory = Path(executable).resolve(), Path(directory).resolve()
    before = source_hashes(directory)
    reports = json.loads((Path(__file__).resolve().parent.parent / 'data/blocks.json').read_text())
    states, defaults, air, fluids = {}, {}, set(), set()
    for name, block in reports.items():
        for state in block['states']:
            properties = state.get('properties', {})
            states[name, tuple(sorted(properties.items()))] = state['id']
            if state.get('default'):
                defaults[name] = state['id']
            if name in ('minecraft:air', 'minecraft:cave_air', 'minecraft:void_air'):
                air.add(state['id'])
            if name in ('minecraft:water', 'minecraft:lava', 'minecraft:bubble_column') or properties.get('waterlogged') == 'true':
                fluids.add(state['id'])
    biome_files = sorted((executable.parent.parent / 'share/mcserver/registries/worldgen/biome').glob('*.json'))
    biome_ids = {'minecraft:' + file.stem: i for i, file in enumerate(biome_files)}

    def resolve(entry):
        if isinstance(entry, str):
            return defaults[entry]
        name = entry.get('id', entry.get(''))
        properties = entry.get('properties', {})
        return states[name, tuple(sorted(properties.items()))] if properties else defaults[name]

    environment_before = os.environ.get('MCSERVER_WORLD_DIR')
    os.environ['MCSERVER_WORLD_DIR'] = str(directory)
    try:
        with tempfile.TemporaryDirectory(prefix='anvil-network-') as temporary:
            overlay = Path(temporary) / 'edits.json'
            with RunningServer(executable, overlay) as server:
                client = Client(server.port, 'Importer', expected_spawn=None)
                try:
                    assert client.current_position[1] > 1, 'still spawned in the flat test world'
                    total = 0
                    for (x, z), data in client.chunks.items():
                        reference = disk_chunk(directory, x, z)
                        wire = network_chunk(data)
                        for section in reference['sections']:
                            y = section['Y'] + 4
                            if not 0 <= y < 24:
                                continue
                            palette = [resolve(entry) for entry in section['block_states']['palette']]
                            blocks = unpack_disk(section['block_states'], palette, 4096, 4)
                            biomes = unpack_disk(section['biomes'], [biome_ids[name] for name in section['biomes']['palette']], 64, 1)
                            count, fluid, actual, actual_biomes = wire[y]
                            assert actual == blocks, f'block mismatch in chunk {(x,z)}, section {y-4}'
                            assert actual_biomes == biomes, 'biome mismatch'
                            assert count == sum(state not in air for state in blocks)
                            assert fluid == sum(state in fluids for state in blocks)
                            total += len(blocks)
                    print(f'PASS: all {total:,} block states, biomes, and fluid counts match the original 9 chunks')
                    px, py, pz = map(math.floor, client.current_position)
                    target = None
                    for y in range(py-1, py-5, -1):
                        for z in range(pz-1, pz+2):
                            for x in range(px-1, px+2):
                                chunk = network_chunk(client.chunks[x//16, z//16])
                                index = (y % 16)*256 + (z % 16)*16 + (x % 16)
                                if chunk[(y+64)//16][2][index] not in air:
                                    target = (x,y,z)
                                    break
                            if target: break
                        if target: break
                    assert target is not None
                    client.action(0, target, 10)
                    client.expect_update(target, 0)
                    client.expect_ack(10)
                finally:
                    client.close()
                assert server.stop() == 0, server.output
            saved = json.loads(overlay.read_text())
            assert saved['world'].startswith('anvil-5023:')
            with RunningServer(executable, overlay) as server:
                client = Client(server.port, 'Reload', expected_spawn=None)
                try:
                    x,y,z = target
                    chunk = network_chunk(client.chunks[x//16,z//16])
                    assert chunk[(y+64)//16][2][(y%16)*256+(z%16)*16+(x%16)] == 0
                finally:
                    client.close()
            print('PASS: an imported terrain edit survives restart in a separate overlay')
        assert source_hashes(directory) == before
        print('PASS: every file in the source world remains unchanged')
    finally:
        if environment_before is None:
            os.environ.pop('MCSERVER_WORLD_DIR', None)
        else:
            os.environ['MCSERVER_WORLD_DIR'] = environment_before


if __name__ == '__main__':
    if len(sys.argv) != 3:
        raise SystemExit('usage: python3 tests/anvil_import_smoke.py path/to/mcserver path/to/world')
    run(sys.argv[1], sys.argv[2])
