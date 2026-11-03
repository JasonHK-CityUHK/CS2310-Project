# CS2310 Project

A minimal C++23 Minecraft Java Edition server for protocol experimentation. The
server currently supports offline login, Configuration registry/tag exchange,
flat-world chunk loading, full-bright lighting, basic Play movement packets, and
keep-alive traffic.

## Requirements

- CMake 3.24 or newer
- A C++23 compiler (GCC 13+ or Clang with C++23 support)
- Git, for CMake FetchContent dependencies
- Internet access during the first configure/build

The build downloads Asio, GlacieTeam/BinaryStream, GlacieTeam/NBT, nlohmann/json,
Catch2, and the official Minecraft 26.3 server bundle.

## Build

From the repository root:

```sh
cmake -S . -B build
cmake --build build --target mcserver -j"$(nproc)"
```

### Windows

Follow these steps in order:

1. Install Visual Studio 2022 with the **Desktop development with C++**
   workload and install CMake.
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
Minecraft server bundle. Registry and data-pack files are generated under:

```text
build/share/mcserver/
├── data/minecraft/   # tags and supplemental data
└── registries/       # synchronized registry JSON files
```

The repository does not need a checked-in copy of these generated files.

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
- A 3x3 empty flat-world chunk area with a stone spawn layer
- Full-bright sky and block light arrays
- Position, rotation, movement flags, teleport confirmation, player-loaded, and
	keep-alive packet handling

Not yet implemented:

- Collision and movement validation
- Block breaking and placement
- Entity movement broadcasting
- Persistent worlds and save/load
