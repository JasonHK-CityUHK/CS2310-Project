#pragma once

#include <nbt/NBT.hpp>

#include <string>
#include <vector>

namespace mcserver::protocol {

// One entry of a synchronized registry, as sent in a Registry Data packet.
struct RegistryEntry {
    std::string id;
    nbt::CompoundTag data;
};

// One synchronized registry (e.g. "minecraft:dimension_type") and its entries.
// Entry order defines the numeric IDs other packets reference, so it must stay stable.
struct Registry {
    std::string id;
    std::vector<RegistryEntry> entries;
};

// Builds the minimal set of registries needed for a vanilla client to accept
// Finish Configuration and enter Play with a single overworld-like dimension.
// This is deliberately minimal (one dimension_type, one biome) and is expected
// to need extending once tested against a real client (see plan Phase 3 notes).
[[nodiscard]] std::vector<Registry> buildMinimalRegistries();

} // namespace mcserver::protocol
