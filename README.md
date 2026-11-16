# CS2310 Project

A minimal C++23 Minecraft Java Edition server for protocol experimentation. The
server currently supports offline login, Configuration registry/tag exchange,
flat-world chunk loading, full-bright lighting, basic Play movement packets,
block breaking and placement with in-memory world updates broadcast to players,
and keep-alive traffic.

## Requirements

- CMake 3.24 or newer
- A C++23 compiler (GCC 13+ or Clang with C++23 support)
- Git, for CMake FetchContent dependencies
- Internet access during the first configure/build

The build downloads Asio, GlacieTeam/BinaryStream, GlacieTeam/NBT, nlohmann/json,
Catch2, and the official Minecraft 26.3 server bundle. The protocol registry
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

The optional port is the first argument to the launcher:

```powershell
.\scripts\run-windows.ps1 25566
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
project directory, run this the first time:

```bat
docker compose build
docker compose up
```

`docker compose build` installs the compiler, CMake, Git, and zlib inside the
image, downloads the C++ dependencies and Minecraft 26.3 data, and builds the
Linux server. `docker compose up` then starts the server. Compose maps the
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

The GitHub Actions snapshot workflow builds and tests on pushes and pull requests.
It uploads a Linux snapshot archive containing the executable, generated
Minecraft runtime data, and a `run-snapshot.sh` launcher. The artifact is retained
for 14 days.

## Run

The server listens on port `25565` by default. A different port can be supplied
as the first argument:

```sh
./build/src/mcserver
./build/src/mcserver 25566
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
- A 3x3 flat-world chunk area with a stone spawn layer
- Read-only import of nine terrain chunks from Minecraft 26.3 Anvil saves
- Full-bright sky and block light arrays
- Player position, rotation, movement flags, teleport confirmation, player-loaded,
  and keep-alive packet handling
- Basic movement checks that reject non-finite coordinates and correct
  per-packet jumps over 10 blocks; collision validation is still pending
- Creative-mode player abilities and an initial inventory
- Block breaking with shared in-memory updates broadcast to other players
- Basic placement of vanilla block items from the hotbar or offhand into air
- Windows build/run scripts and Docker configuration
- JSON save/load of broken and placed block states across server restarts
- Automatic saves every five seconds and a final save on normal shutdown
- Failed-save retries, corrupt-save protection, and legacy version 1 save compatibility
- A Docker Compose volume for retaining world saves across container recreation

Not yet implemented:

- Collision detection and comprehensive movement validation
- Entity movement broadcasting
- General-version world support, original-world write-back, and entity persistence

## World Persistence

Modified block states are saved to `world/flat-world.json`, relative to the
working directory. Set `MCSERVER_WORLD_FILE` to choose another path. Each running
server must use a separate save file. Vanilla registry/report data remains
separate from the writable world save.

Changed worlds autosave every five seconds and once more on Ctrl+C (SIGINT) or
SIGTERM. A forced kill may lose changes since the last successful save. Snapshots
are written to a neighboring `.tmp` file, closed, then renamed over the save.
Write failures preserve the last complete save and are retried at the next tick;
a failed final save exits with status 1. Missing saves start a new world. Corrupt,
invalid, or incompatible saves stop startup without overwriting the file.

Version 2 stores block overrides as `blocks` entries with integer `x`, `y`, `z`,
and `state`, together with `protocol: 777` and `world: "flat-stone-v1"`. Both
broken blocks (state 0) and placed blocks are restored. Legacy version 1
`broken_blocks` saves from the earlier flat-world prototype are accepted and
upgraded on the next successful save. States are validated against the generated
vanilla block report. The format is not Minecraft Anvil. Saves are limited to
100,000 overrides and 32 MiB; coordinate height is -64..319.

```sh
MCSERVER_WORLD_FILE=world/demo.json ./build/src/mcserver
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

## Read-only Minecraft 26.3 World Import

Set `MCSERVER_WORLD_DIR` to a **copy** of a vanilla Java 26.3 world folder
(DataVersion 5023). The loader reads named-root, big-endian disk NBT from
`level.dat` and `dimensions/minecraft/overworld/region/r.*.*.mca`. It supports
in-region gzip, zlib, and uncompressed chunks, string/compound block palettes,
block properties, negative region coordinates, and biome palettes.

The server loads nine fully generated chunks around the last saved single-player
Overworld position when that player's data is available; otherwise it uses the
level spawn. This initial implementation has a fixed 3x3 view, retains full-bright
lighting, and does not load entities, block-entity content, or simulate redstone.
Other DataVersions, dimensions, LZ4/custom compression, external `.mcc` chunks,
missing chunks, and unknown block states produce explicit startup errors.

```sh
MCSERVER_WORLD_DIR="/path/to/copied-world" \
MCSERVER_WORLD_FILE="world/imported-edits.json" \
./build/src/mcserver 25566
```

Connect the 26.3 client to `localhost:25566`. The source world is opened for reading
only. Mining/placement changes go to the separate JSON overlay, never to `.mca`
or `level.dat`. Without `MCSERVER_WORLD_FILE`, import mode uses
`world/imported.json`. Each overlay records a fingerprint of the loaded source
chunks; a different or modified source is rejected rather than receiving the
wrong edits. Keep the source snapshot unchanged for subsequent overlay loads.
Legacy flat-world saves are kept separate. Leaving `MCSERVER_WORLD_DIR` unset
preserves the original flat-world mode.

Tests:

```sh
ctest --test-dir build --output-on-failure
python3 tests/anvil_import_smoke.py build/src/mcserver /path/to/copied-world
```

The four generated Anvil fixture tests need no personal world files. The optional
real-world TCP test independently decodes the source map, compares all 884,736
block states and biome cells sent in the nine chunks, checks terrain edits across
a restart, and verifies source-file hashes remain unchanged. Do not commit
personal test worlds or player data to the repository.
