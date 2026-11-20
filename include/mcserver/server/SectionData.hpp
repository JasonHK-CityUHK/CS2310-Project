#pragma once

#include <nbt/NBT.hpp>

#include <array>
#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace mcserver::server {

using BlockStateResolver = std::function<int32_t(nbt::CompoundTagVariant const&)>;
using ChunkSections = std::array<std::array<int32_t, 4096>, 24>;
using BiomeSections = std::array<std::array<int32_t, 64>, 24>;

class BlockStateRegistry {
public:
    BlockStateRegistry();
    [[nodiscard]] int32_t resolve(nbt::CompoundTagVariant const& entry) const;
    [[nodiscard]] nbt::CompoundTag paletteEntry(int32_t state) const;
    [[nodiscard]] bool isAir(int32_t state) const { return airStates_.contains(state); }
    [[nodiscard]] bool hasFluid(int32_t state) const { return fluidStates_.contains(state); }

private:
    std::unordered_map<std::string, int32_t> states_;
    std::unordered_map<int32_t, nbt::CompoundTag> entries_;
    std::unordered_set<int32_t> airStates_;
    std::unordered_set<int32_t> fluidStates_;
};

[[nodiscard]] std::array<int32_t, 4096> decodeBlockStates(
    nbt::CompoundTag const& blockStates, BlockStateResolver const& resolve);
[[nodiscard]] nbt::CompoundTag encodeBlockStates(std::array<int32_t, 4096> const& states,
                                                 BlockStateRegistry const& registry);
[[nodiscard]] ChunkSections decodeChunkSections(nbt::CompoundTag const& chunk,
                                                BlockStateResolver const& resolve);
[[nodiscard]] BiomeSections decodeChunkBiomes(nbt::CompoundTag const& chunk,
                                              std::unordered_map<std::string, int32_t> const& biomes);

} // namespace mcserver::server
