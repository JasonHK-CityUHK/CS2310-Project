#pragma once

#include <nbt/NBT.hpp>

#include <filesystem>
#include <string>
#include <vector>

namespace mcserver::protocol {

// One entry of a synchronized registry, as sent in a Registry Data packet.
struct RegistryEntry {
    std::string id;
    nbt::CompoundTagVariant data;
};

// One synchronized registry (e.g. "minecraft:dimension_type") and its entries.
// Entry order defines the numeric IDs other packets reference, so it must stay stable.
struct Registry {
    std::string id;
    std::vector<RegistryEntry> entries;
};

// Loads every registry bundled under `root` (see data/registries/ — real vanilla
// data pack JSON extracted from the client jar for this exact protocol version,
// see plan/repo memory for how it was obtained). Each immediate subdirectory of
// `root` is treated as one registry (e.g. `root/dimension_type/*.json` becomes
// registry "minecraft:dimension_type"), except `root/worldgen/biome/*.json`
// which is special-cased to registry "minecraft:worldgen/biome". JSON files that
// fail to parse as NBT are skipped with a warning rather than aborting the load.
[[nodiscard]] std::vector<Registry> loadRegistriesFromDirectory(std::filesystem::path const& root);

// Loads the registries bundled with this build (data/registries/, embedded via
// the MCSERVER_REGISTRY_DATA_DIR compile definition — see src/CMakeLists.txt).
[[nodiscard]] std::vector<Registry> buildMinimalRegistries();

} // namespace mcserver::protocol

