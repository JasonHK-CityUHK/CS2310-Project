"""Run the opt-in world reader test against an archive without changing its contents."""
import os
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import zipfile
import zlib

from persistence_client import Client, chunk_state
from world_persistence_smoke import RunningServer, create_world


def test_java_lz4(root, server_executable):
    jar = Path(__file__).resolve().parent.parent / 'libraries/at/yawk/lz4/lz4-java/1.10.1/lz4-java-1.10.1.jar'
    java = shutil.which('java')
    if not java or not jar.is_file():
        print('SKIP: Java LZ4 interoperability requires the bundled LZ4 Java library and Java')
        return
    fixture_root = root / 'lz4-fixture'
    fixture_root.mkdir()
    world = create_world(fixture_root)
    region_path = world / 'dimensions/minecraft/overworld/region/r.0.0.mca'
    region = bytearray(region_path.read_bytes())
    length = struct.unpack_from('>I', region, 8192)[0]
    nbt = zlib.decompress(region[8197:8192 + 4 + length])
    source = fixture_root / 'JavaLz4Fixture.java'
    source.write_text('import net.jpountz.lz4.LZ4BlockOutputStream;\n'
                      'class JavaLz4Fixture { public static void main(String[] args) throws Exception {\n'
                      'var output = new LZ4BlockOutputStream(System.out);\n'
                      'System.in.transferTo(output); output.close(); } }\n')
    result = subprocess.run([java, '--class-path', str(jar), str(source)], input=nbt,
                            capture_output=True, check=True)
    record = struct.pack('>IB', len(result.stdout) + 1, 4) + result.stdout
    assert len(record) <= 4096
    region[8192:12288] = record.ljust(4096, b'\0')
    region_path.write_bytes(region)
    with RunningServer(server_executable, fixture_root) as server:
        player = Client(server.port, 'Lz4Tester', expected_spawn=(8.5, 8., 8.5))
        try:
            assert chunk_state(player.chunks[0, 0], 8, 8, y=8)[0] == 1
            player.action(0, (8, 8, 8), 1)
            player.expect_update((8, 8, 8), 0)
            player.expect_ack(1)
        finally:
            player.close()
    with RunningServer(server_executable, fixture_root) as server:
        player = Client(server.port, 'Lz4Reload', expected_spawn=(8.5, 8., 8.5))
        try:
            assert chunk_state(player.chunks[0, 0], 8, 8, y=8)[0] == 0
        finally:
            player.close()
    print('PASS: Java-compressed LZ4 chunk loads, saves, and reloads')


def main(archive, executable, server_executable=None):
    with tempfile.TemporaryDirectory(prefix='mcserver-vanilla-world-') as directory:
        root = Path(directory)
        with zipfile.ZipFile(archive) as world:
            for entry in world.infolist():
                path = Path(entry.filename)
                if path.is_absolute() or '..' in path.parts:
                    raise ValueError(f'unsafe archive entry: {entry.filename}')
                world.extract(entry, root)
        environment = dict(os.environ, MCSERVER_TEST_WORLD_DIR=str(root / 'Sample'))
        subprocess.run([str(Path(executable).resolve()), '[sample-world]'], env=environment, check=True)
        if server_executable:
            (root / 'Sample').rename(root / 'selected-world')
            with RunningServer(server_executable, root) as server:
                player = Client(server.port, 'SampleTester', expected_spawn=(-31.5, 69., .5), expected_chunks=None)
                try:
                    assert (-2, 0) in player.chunks, 'spawn chunk was not sent'
                    state, count = chunk_state(player.chunks[-2, 0], -32, 0, y=69)
                    assert state >= 0 and 0 <= count <= 4096
                finally:
                    player.close()
            print('PASS: supplied Java world starts and sends its spawn chunk over TCP')
            test_java_lz4(root, server_executable)


if __name__ == '__main__':
    if len(sys.argv) not in (3, 4):
        raise SystemExit('usage: python3 tests/java_world_sample.py world.zip mcserver_tests [mcserver]')
    main(*sys.argv[1:])
