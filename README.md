# CS2310 Project

A minimal C++23 Minecraft Java Edition server for protocol experimentation. The
server currently supports offline login, Configuration registry/tag exchange,
loading existing Java 26.3 overworld chunks, basic Play movement packets,
restricted block edits, persistent player profiles, and keep-alive traffic.

## Requirements

- CMake 3.24 or newer
- C and C++23 compilers (GCC 13+ or Clang with C++23 support)
- Git, for CMake FetchContent dependencies
- Internet access during the first configure/build
- zlib development support

Docker mode has no native CMake, compiler, vcpkg, or zlib requirement on the
host. Docker installs and runs those tools inside the Linux build image.

The build downloads Asio, GlacieTeam/BinaryStream, GlacieTeam/NBT, LZ4,
nlohmann/json, Catch2, and the official Minecraft 26.3 server bundle. The protocol registry
and block-state ID reports must be present in `data/blocks.json` and
`data/registries.json`; CMake copies these files into the runtime data directory.
Neither Java nor Go is required.

## Build

From the repository root:

```sh
cmake -S . -B build
cmake --build build --target mcserver -j"$(nproc)"
```

### Windows

Follow these steps in order:

1. Install Visual Studio 2022 with the **Desktop development with C++** workload.
2. Choose a directory for vcpkg, then install it from the official Microsoft
   repository:

```powershell
git clone https://github.com/microsoft/vcpkg.git (Join-Path $HOME "vcpkg")
cd (Join-Path $HOME "vcpkg")
.\bootstrap-vcpkg.bat
```

3. Open PowerShell in the project directory:

```powershell
cd "<your project directory>"
```

4. Build the server. Pass the same vcpkg directory to the script:

```powershell
.\scripts\build-windows.ps1 -VcpkgRoot (Join-Path $HOME "vcpkg")
```

If you chose a different directory, replace `(Join-Path $HOME "vcpkg")` with
your own vcpkg directory. This step installs zlib, configures a Visual Studio
x64 build, downloads the required Minecraft data, and compiles the executable.

5. Start the server:

```powershell
.\scripts\run-windows.ps1
```

Keep this PowerShell window open. The server must remain running while
Minecraft connects. You should see:

```text
[INFO] [mcserver] listening on port 25565
```

6. In Minecraft Java Edition **26.3**, open Multiplayer and connect to:

```text
localhost
```

To use another port, add `server-port=25566` to `server.properties` in the
working directory, then run:

```powershell
.\scripts\run-windows.ps1
```

For that example, connect to `localhost:25566` in Minecraft.

`build-windows.ps1` is an optional shortcut for the build commands.
`run-windows.ps1` is an optional shortcut that starts an already-built server
and sets `MCSERVER_DATA_DIR` to the generated data. Neither script requires a
specific drive letter or project directory.

The first build downloads and extracts the nested server jar from the official
Minecraft server bundle for tags and supplemental registry data. It copies the
provided block-state and registry reports from `data/`. Runtime files are
prepared under:

```text
build/share/mcserver/
├── data/minecraft/   # tags and supplemental data
├── data/reports/     # protocol registry and block-state ID JSON reports
└── registries/       # synchronized registry JSON files
```

Keep `data/blocks.json` and `data/registries.json` in the repository's root
`data/` directory; they are source inputs, not build outputs.

### Docker

Docker Desktop is an alternative to installing the C++ toolchain locally.
The Docker commands below work in Command Prompt or PowerShell. You only need
Docker Desktop with its Linux container engine enabled; you do not need to
install CMake, vcpkg, a C++ compiler, Git, or zlib on Windows. From the
project directory, run this after copying an existing world:

```bat
docker compose build
docker compose create
docker compose cp "X:\path\to\Your World\." mcserver:/opt/mcserver/world/
docker compose up -d
```

`docker compose build` installs the compiler, CMake, Git, and zlib inside the
image, downloads the C++ dependencies and Minecraft 26.3 data, and builds the
Linux server and runs the CMake test suite. Replace the example path with the
complete extracted Java 26.3 world directory. The world directory must contain
`level.dat` and `dimensions`. The copy step populates the persistent volume.
There is no world generator or fallback template.

Compose maps the
host's port `25565` to the container's port `25565`, so connect Minecraft Java
Edition **26.3** to:

```text
localhost
```

After the image has been built successfully, start it normally with:

```bat
docker compose up
```

You only need to rebuild after changing source files, `Dockerfile`,
`docker-compose.yml`, or dependencies:

```bat
docker compose build
docker compose up
```

To build and start in one command, you can use `docker compose up --build`.
To run the server in the background:

```bat
docker compose up -d
docker compose logs -f
```

Stop and remove the container with:

```bat
docker compose down
```

To use a different host port, set `MCSERVER_HOST_PORT` in the command:

```bat
set MCSERVER_HOST_PORT=25566
docker compose up
```

Then connect to `localhost:25566`. Docker runs the Linux server in a
container; it does not produce a native Windows `.exe`.

To use a separate build directory or compiler, pass the usual CMake options:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j"$(nproc)"
```

## Tests

```sh
ctest --test-dir build --output-on-failure
```

To check the standalone reader against a zipped world whose root directory is
named `Sample`, build `mcserver_tests` and run:

```sh
python3 tests/java_world_sample.py /path/to/world.zip build/tests/mcserver_tests build/src/mcserver
```

The archive is extracted into a temporary directory for the test.

The GitHub Actions snapshot workflow builds and tests on pushes and pull requests.
It uploads a Linux snapshot archive containing the executable, generated
Minecraft runtime data, and a `run-snapshot.sh` launcher. The artifact is retained
for 14 days.

## Run

The server reads `server.properties` in its working directory. It supports
`server-ip` (empty means all IPv4 interfaces), `server-port` (default 25565),
`motd` (default `CS2310 minimal MC server`), `view-distance` (default 10,
range 3-32), and `level-name` (default `world`).
Other settings are ignored. `level-name` identifies an existing extracted world
directory relative to the working directory. Native and Docker startup do not
create worlds or generate missing chunks. Extract an existing world and set:

```properties
server-ip=127.0.0.1
server-port=25566
motd=My Minecraft server
level-name=Sample
```

Logging defaults to `info`. Set `MCSERVER_LOG_LEVEL` to `error`, `warning`,
`info`, or `debug` to change the minimum severity. Debug mode includes incoming
Play packet IDs:

```sh
MCSERVER_LOG_LEVEL=debug ./build/src/mcserver
```

Connect with a Minecraft Java Edition 26.3 client using offline/local server
mode.

## Current Scope

Implemented:

- Handshake, Status, Login, Configuration, and Play state transitions
- Offline UUID login without encryption or compression
- Runtime registry and tag packets sourced from the official server data pack
- Existing Java 26.3 overworld chunks streamed around the saved spawn and players
- Nearby chunks sent first in client-paced, acknowledged batches, with the
  remaining configured view streamed afterward
- Saved biome palettes and light arrays in chunk packets
- Player position, rotation, movement flags, teleport confirmation, player-loaded,
  and keep-alive packet handling
- Basic movement checks that reject non-finite coordinates and correct
  per-packet jumps over 10 blocks; collision validation is still pending
- Creative-mode player abilities and a persistent player inventory
- UUID-keyed player profiles with hotbar, main inventory, armor, offhand,
  selected slot, position, rotation, and on-ground state
- Vanilla block placement into air and breaking of supported blocks in
  Java-world chunks, with updates shared by connected players
- Windows build/run scripts and Docker configuration
- Java level metadata and Anvil region loading and saving
- Automatic saves every five seconds and a final save on normal shutdown
- Failed-save retries and corrupt-save protection
- A Docker Compose volume for retaining world saves across container recreation

Not yet implemented:

- Collision detection and comprehensive movement validation
- Entity movement broadcasting
- New-world or chunk generation, other dimensions, and entity persistence
- Block entity simulation

## World Persistence

Worlds must be existing Java 26.3 saves with data version 5023. The server
locks `session.lock` while running and reads the Overworld's region files under
`dimensions/minecraft/overworld/region`. It supports gzip, zlib, uncompressed,
and Java LZ4 chunks, including external chunks for reading. External chunk
writes are not supported. Other dimensions and unsupported world files are not changed.
Back up a world before using it: opening a saved world in the vanilla client
after edits has not yet been verified.

Missing chunks are not generated. If a player's saved position is in a missing
chunk, the server logs a warning and the client may remain on the loading
screen until its timeout.

Block items can be placed into air, and non-air blocks can be broken in
supported loaded chunks. Edits are rejected at chunk boundaries and in chunks
with block entities, pending block/fluid ticks, point-of-interest data, or
external chunk storage. Block behavior and block entity simulation are not
implemented.

Changed worlds autosave every five seconds and once more on Ctrl+C (SIGINT) or
SIGTERM. A forced kill may lose changes since the last successful save. Region
updates are written to a neighboring temporary file and atomically replaced.
Write failures preserve the last complete region and are retried; a failed final
save exits with status 1. Missing, corrupt, or incompatible worlds stop startup.
Saves across different regions are not an atomic transaction.

```sh
ctest --test-dir build --output-on-failure
python3 tests/world_persistence_smoke.py build/src/mcserver
```

The TCP smoke test uses temporary ports and saves and checks mining, placing,
restart recovery, timed saving, failed-write retries, and corrupt-save protection.
It runs on POSIX and needs Python 3. Windows users should use Ctrl+C for normal
shutdown; externally terminating a Windows process can bypass final saving.
A real Minecraft client should also be used before classroom demonstration.

Docker Compose mounts a named volume at `/opt/mcserver/world`. Normal
`docker compose down` retains the save; `docker compose down -v` deletes it.
Player inventories are saved as JSON files under
`<level-name>/playerdata/<offline-UUID>.json`. The selected hotbar slot,
main inventory, armor, hotbar, and offhand are restored after reconnecting.
The player's position, yaw, pitch, and on-ground state are saved in the same
profile every ten seconds, when the player disconnects, and during normal
shutdown.

The JSON player profile is an implementation-specific persistence format; it
is not a vanilla Java `playerdata/<uuid>.dat` file. A profile is written only
for players that have entered Play. Corrupt or incompatible profiles are
reported during join and are replaced with the default profile by the session;
the server does not silently modify a world region as a fallback.
