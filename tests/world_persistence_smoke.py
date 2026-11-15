"""Test disk persistence through real TCP clients and real server restarts.
Run: python3 tests/world_persistence_smoke.py build/src/mcserver
"""
import json
import os
from pathlib import Path
import signal
import socket
import subprocess
import sys
import tempfile
import time

from persistence_client import Client, chunk_state


class RunningServer:
    def __init__(self, executable, world_file):
        self.executable = str(Path(executable).resolve())
        self.world_file = Path(world_file)
        self.environment = dict(os.environ, MCSERVER_WORLD_FILE=str(world_file))
        self.process = None

    def __enter__(self):
        with socket.socket() as probe:
            probe.bind(('127.0.0.1', 0))
            self.port = probe.getsockname()[1]
        self.process = subprocess.Popen([self.executable, str(self.port)], env=self.environment,
                                        stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
        deadline = time.monotonic() + 5
        while True:
            if self.process.poll() is not None:
                output = self.process.communicate()[0]
                raise AssertionError('server did not start: ' + output)
            try:
                with socket.create_connection(('127.0.0.1', self.port), timeout=.1):
                    return self
            except OSError:
                if time.monotonic() >= deadline:
                    self.process.kill()
                    output = self.process.communicate()[0]
                    raise AssertionError('server startup timed out: ' + output)
                time.sleep(.02)

    def stop(self, shutdown_signal=signal.SIGTERM):
        self.process.send_signal(shutdown_signal)
        self.output = self.process.communicate(timeout=5)[0]
        return self.process.returncode

    def crash(self):
        self.process.kill()
        self.output = self.process.communicate(timeout=5)[0]

    def __exit__(self, *_):
        if self.process.poll() is None:
            try:
                self.stop()
            except subprocess.TimeoutExpired:
                self.crash()


def mine(server, point, sequence=1):
    client = Client(server.port, 'SaveTester')
    try:
        x, y, z = point
        client.move(x + .5, y + 1, z + .5)
        client.action(0, point, sequence)
        client.expect_update(point, 0)
        client.expect_ack(sequence)
    finally:
        client.close()


def assert_holes(server, points):
    client = Client(server.port, 'ReloadTester')
    try:
        for x, _, z in points:
            state, _ = chunk_state(client.chunks[x // 16, z // 16], x, z)
            assert state == 0, 'saved hole disappeared after restart'
        assert chunk_state(client.chunks[1, 1], 20, 20) == (1, 256)
    finally:
        client.close()


def wait_for_blocks(path, expected):
    deadline = time.monotonic() + 9
    while time.monotonic() < deadline:
        if path.exists():
            snapshot = json.loads(path.read_text())  # a visible save must always be complete JSON
            if len(snapshot['blocks']) == expected:
                assert snapshot['version'] == 2
                return
        time.sleep(.05)
    raise AssertionError('autosave did not produce expected snapshot')


def run(executable):
    executable = str(Path(executable).resolve())
    with tempfile.TemporaryDirectory(prefix='mcserver-persistence-') as directory:
        path = Path(directory) / 'world' / 'flat-world.json'
        first = (-1, 0, -1)
        second = (0, 0, 0)
        third = (1, 0, 0)
        with RunningServer(executable, path) as server:
            mine(server, first)
            assert server.stop(signal.SIGINT) == 0, server.output
        snapshot = json.loads(path.read_text())
        assert snapshot['blocks'] == [{'x': -1, 'y': 0, 'z': -1, 'state': 0}]
        print('PASS: Ctrl+C saves the changed world before exiting')

        with RunningServer(executable, path) as server:
            assert_holes(server, [first])
            placer = Client(server.port, 'Placer')
            placer.move(2.5, 1., 2.5)
            # Select vanilla stone in creative hotbar slot 36, then place it on the ground.
            from persistence_client import varint, position
            import struct
            placer.send(0x39, struct.pack('>h', 36) + varint(1) + varint(1) + varint(0) + varint(0))
            placer.send(0x42, varint(0) + position(2, 0, 2) + varint(1) + struct.pack('>fff??', .5, 1., .5, False, False) + varint(3))
            placer.expect_update((2, 1, 2), 1)
            placer.expect_ack(3)
            placer.close()
            mine(server, second)
            wait_for_blocks(path, 3)
            server.crash()  # autosaved state must survive a forced stop too
        with RunningServer(executable, path) as server:
            assert_holes(server, [first, second])
            observer = Client(server.port, 'PlacementObserver')
            try:
                assert chunk_state(observer.chunks[0, 0], 2, 2, y=1)[0] == 1
            finally:
                observer.close()
        print('PASS: timer autosave survives a forced stop and reloads into chunk packets')

        original = path.read_bytes()
        temporary = Path(str(path) + '.tmp')
        with RunningServer(executable, path) as server:
            temporary.mkdir()
            mine(server, third)
            time.sleep(5.2)  # allow one failed timer save
            assert path.read_bytes() == original, 'failed save overwrote the last good snapshot'
            temporary.rmdir()
            wait_for_blocks(path, 4)
            assert server.stop() == 0, server.output
            assert 'cannot save world' in server.output, 'expected the first save attempt to fail'
        with RunningServer(executable, path) as server:
            assert_holes(server, [first, second, third])
        print('PASS: failed autosave preserves the old snapshot and retries successfully')

        original = path.read_bytes()
        with RunningServer(executable, path) as server:
            temporary.mkdir()
            mine(server, (2, 0, 0))
            assert server.stop() == 1, 'failed final save must produce a nonzero exit code'
            assert 'cannot save world' in server.output
        assert path.read_bytes() == original
        temporary.rmdir()
        print('PASS: a failed final save reports failure and preserves the previous snapshot')

        for bad_save in ['{broken json', '{"version":2,"world":"flat-stone-v1","broken_blocks":[]}']:
            path.write_text(bad_save)
            environment = dict(os.environ, MCSERVER_WORLD_FILE=str(path))
            result = subprocess.run([executable, '0'], env=environment, capture_output=True,
                                    text=True, timeout=5)
            assert result.returncode == 1
            assert 'cannot load world' in result.stderr
            assert path.read_text() == bad_save, 'invalid source save was replaced'
        print('PASS: corrupt and incompatible saves prevent startup without overwriting the file')


if __name__ == '__main__':
    if len(sys.argv) != 2:
        raise SystemExit('usage: python3 tests/world_persistence_smoke.py path/to/mcserver')
    run(sys.argv[1])
