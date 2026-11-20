#pragma once

#include <nbt/NBT.hpp>

#include <cstdint>
#include <filesystem>
#include <optional>

namespace mcserver::server {

class WorldLock;

[[nodiscard]] std::optional<nbt::CompoundTag> loadRegionChunk(
    std::filesystem::path const& worldDirectory, int32_t chunkX, int32_t chunkZ, bool* external = nullptr);
void saveRegionChunk(WorldLock const& lock, std::filesystem::path const& worldDirectory, int32_t chunkX, int32_t chunkZ,
                     nbt::CompoundTag const& chunk);

} // namespace mcserver::server
