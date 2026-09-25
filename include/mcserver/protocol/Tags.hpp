#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace mcserver::protocol {

// One tag within a registry (e.g. "minecraft:infiniburn_overworld" on "minecraft:block"),
// referencing entries by their numeric ID within that registry.
struct TagDefinition {
    std::string name;
    std::vector<int32_t> entries;
};

// All tags declared for a single registry, as sent in one Update Tags packet entry.
struct TaggedRegistry {
    std::string registryId;
    std::vector<TagDefinition> tags;
};

// Builds the minimal set of tags referenced by mcserver::protocol::buildMinimalRegistries()
// (currently just enough for the block tags our dimension_type entries reference via "infiniburn").
[[nodiscard]] std::vector<TaggedRegistry> buildMinimalTags();

} // namespace mcserver::protocol
