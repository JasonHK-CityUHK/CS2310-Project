# AGENTS.md

## Project

CS2310-Project is a C++23 Minecraft Java Edition server used for protocol experimentation. The target client is Minecraft 26.3 with protocol version 777.

The server currently supports:

- Handshake, Status, Login, Configuration, and Play state transitions
- Offline-mode login without encryption or compression
- Runtime registry and tag packets
- A 3x3 flat-world chunk area with a stone spawn layer
- Full-bright sky and block lighting
- Basic player movement, rotation, teleport confirmation, player-loaded, and keep-alive packets

Collision validation, block interaction, entity broadcasting, and persistence are not implemented yet.

## Repository Layout

- `include/mcserver/`: public C++ headers
- `src/net/`: packet framing, byte readers/writers, and connection handling
- `src/protocol/`: NBT, JSON conversion, registry, and tag encoding
- `src/server/`: client-session state machine and server startup
- `tests/`: Catch2 tests
- `references/`: checked-in Minecraft protocol and chunk-format references
- `cmake/`: dependency and Minecraft data extraction logic
- `build/`: generated build files, downloaded dependencies, and extracted Minecraft data; never commit it

## Build Requirements

- CMake 3.24 or newer
- A C++23 compiler, preferably GCC 13+ or a current Clang
- Git, because dependencies are fetched with CMake FetchContent
- Internet access for the first configure/build, to fetch C++ dependencies and the official Minecraft server bundle

Dependencies are pinned in `cmake/Dependencies.cmake`:

- Asio 1.38.2
- GlacieTeam/BinaryStream 2.3.2
- GlacieTeam/NBT 2.6.3
- nlohmann/json 3.11.3
- Catch2 3.16.0

## Standard Commands

Run commands from the repository root:

```sh
cmake -S . -B build
cmake --build build --target mcserver -j"$(nproc)"
ctest --test-dir build --output-on-failure
```

For a clean debug configuration:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j"$(nproc)"
```

Run the server on the default port:

```sh
./build/src/mcserver
```

Run on another port:

```sh
./build/src/mcserver 25566
```

The executable listens on port 25565 by default. Do not start a second server on a port already in use; inspect or stop the existing process first.

## Generated Minecraft Data

Minecraft data is not source-controlled. The `mcserver_data` CMake target downloads the pinned official Minecraft 26.3 server bundle, verifies its SHA-1, extracts the nested jar at `META-INF/versions/*/server-*.jar`, and generates:

```text
build/share/mcserver/
├── data/minecraft/   # extracted vanilla data pack, including tags
└── registries/       # curated synchronized registry JSON files
```

The loader receives these paths through compile definitions:

- `MCSERVER_REGISTRY_DATA_DIR`
- `MCSERVER_TAG_DATA_DIR`
- `MCSERVER_VANILLA_DATA_DIR`

Do not restore generated JSON into the repository or hard-code source-tree data paths. If the Minecraft version changes, update the version, URL, and SHA-1 together in the top-level `CMakeLists.txt`, then verify registry ordering and client compatibility.

## Protocol Conventions

- Verify packet IDs against the checked-in references and the target Minecraft version before changing them.
- Clientbound and serverbound packet IDs use separate ID spaces; do not assume an ID is shared between directions.
- Keep packet field order and primitive widths exact. VarInt, VarLong, fixed-width integers, byte arrays, BitSets, UUIDs, and NBT are not interchangeable.
- Use `ByteReader` and `ByteWriter` from `include/mcserver/net/ByteBuffer.hpp` for protocol primitives.
- `Connection` owns packet framing and asynchronous writes. Session code should handle packet meaning, not TCP framing.
- The connection is currently uncompressed and offline-mode. Do not add compression or encryption assumptions without updating the state machine and handshake flow.
- Play movement data is currently recorded as session state. Do not describe it as collision-validated or authoritative until those systems exist.

Important current Play packet IDs for protocol 777 are defined near the top of `src/server/ClientSession.cpp`. Keep those constants centralized and documented when adding more packets.

## Registry and NBT Rules

- Registry entry order determines numeric IDs used by later packets. Preserve deterministic sorting.
- Use the project JSON-to-NBT conversion path in `src/protocol/JsonToNbt.cpp`; do not reintroduce the known integer-width truncation bug from the library conversion helper.
- Use `src/protocol/Nbt.cpp` for Java network NBT encoding.
- Tags must reference registries actually sent during Configuration. Avoid sending tags for absent registries.
- When adding a registry, update the extraction selection in `cmake/DownloadMinecraftData.cmake` only if the protocol requires it, then validate the resulting Configuration phase with a real client.

## Chunk Rules

- The current overworld is 384 blocks tall with `min_y = -64`, so it has 24 chunk sections and 26 light-mask positions including the two boundary sections.
- Chunk section serialization must match the 26.3 codec exactly: block count, fluid count, block paletted container, then biome paletted container.
- Minecraft 1.21.5+ paletted data arrays do not include a separate array-length field; the length is derived from bits per entry and entry count.
- Java network `BitSet` values are encoded as length-prefixed little-endian byte arrays, not as long arrays.
- For chunk changes, prefer a focused packet-layout test or byte-count check before testing with the client.

## Editing and Validation Workflow

Before editing:

1. Find the owning implementation and a nearby test or protocol reference.
2. State the smallest local hypothesis about the behavior.
3. Make the smallest change that can disprove or confirm it.

After the first substantive edit:

1. Run the narrowest relevant executable check immediately.
2. Repair failures in the same slice before expanding scope.
3. Finish with at least one executable validation step.

For normal C++ or CMake changes, run:

```sh
cmake --build build --target mcserver -j"$(nproc)"
ctest --test-dir build --output-on-failure
```

Use `get_errors` or the project compiler diagnostics for touched files when available. Do not treat `git diff` alone as validation when a focused build or test exists.

## Code Style

- Follow the surrounding C++ style and keep public APIs stable unless the task requires a change.
- Prefer clear, descriptive names over one-letter variables.
- Keep changes focused; avoid unrelated refactors and formatting churn.
- Use ASCII by default.
- Add comments only where they clarify protocol details or non-obvious constraints.
- Do not add license or copyright headers.
- Do not commit, reset, checkout, or create branches unless explicitly requested.
- Never overwrite or revert unrelated user changes in a dirty worktree.

## Documentation

Update `README.md` when build prerequisites, generated data behavior, supported protocol scope, or user-facing commands change. Keep `AGENTS.md` focused on collaboration and repository conventions; do not duplicate the full protocol reference here.

## Common Pitfalls

- Building from a stale CMake configuration after changing CMake paths; rerun `cmake -S . -B build`.
- Running the server against stale generated data after changing the extraction script; remove or regenerate the build data stamp if necessary.
- Using root `data/` or `share/data/` as runtime inputs; authoritative generated data is under `build/share/mcserver/`.
- Sending a packet with the right fields in the wrong order or with the wrong integer encoding.
- Forgetting that a real client may send Play packets immediately after entering the world; unsupported packets should be intentionally ignored or handled without corrupting the next frame.
- Leaving a server process running on the port needed by tests or manual client validation.
