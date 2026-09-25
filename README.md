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

The first build downloads and extracts the nested server jar from the official
Minecraft server bundle. Registry and data-pack files are generated under:

```text
build/share/mcserver/
├── data/minecraft/   # tags and supplemental data
└── registries/       # synchronized registry JSON files
```

The repository does not need a checked-in copy of these generated files.

To use a separate build directory or compiler, pass the usual CMake options:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j"$(nproc)"
```

## Tests

```sh
ctest --test-dir build --output-on-failure
```

## Run

The server listens on port `25565` by default. A different port can be supplied
as the first argument:

```sh
./build/src/mcserver
./build/src/mcserver 25566
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
