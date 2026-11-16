#include "mcserver/server/ChunkData.hpp"

#include "mcserver/net/ByteBuffer.hpp"
#include "mcserver/server/World.hpp"

#include <algorithm>
#include <array>
#include <bit>
#include <unordered_map>
#include <vector>

namespace mcserver::server {
namespace {

template<size_t Count>
void writePalettedContainer(net::ByteWriter& writer, std::array<int32_t, Count> const& blockStates,
                            size_t blockCount, uint8_t globalBitsPerEntry, uint8_t minBits = 4,
                            uint8_t maxLocalBits = 8) {
    std::vector<int32_t> palette;
    std::unordered_map<int32_t, uint32_t> paletteIndices;
    if (blockCount != blockStates.size()) {
        palette.push_back(0);
        paletteIndices.emplace(0, 0);
    }
    for (int32_t blockState : blockStates) {
        if (!paletteIndices.contains(blockState)) {
            paletteIndices.emplace(blockState, static_cast<uint32_t>(palette.size()));
            palette.push_back(blockState);
        }
    }

    if (palette.size() == 1) {
        writer.writeUByte(0);
        writer.writeVarInt(palette.front());
        return;
    }

    uint8_t bitsPerEntry =
        std::max<uint8_t>(minBits, static_cast<uint8_t>(std::bit_width(palette.size() - 1)));
    bool useGlobalPalette = bitsPerEntry > maxLocalBits;
    if (useGlobalPalette) {
        bitsPerEntry = globalBitsPerEntry;
        writer.writeUByte(bitsPerEntry);
    } else {
        writer.writeUByte(bitsPerEntry);
        writer.writeVarInt(static_cast<int32_t>(palette.size()));
        for (int32_t blockState : palette) { writer.writeVarInt(blockState); }
    }

    size_t entriesPerLong = 64 / bitsPerEntry;
    std::vector<uint64_t> data((blockStates.size() + entriesPerLong - 1) / entriesPerLong, 0);
    for (size_t index = 0; index < blockStates.size(); ++index) {
        uint32_t value = useGlobalPalette ? static_cast<uint32_t>(blockStates[index])
                                          : paletteIndices.at(blockStates[index]);
        size_t bitOffset = (index % entriesPerLong) * bitsPerEntry;
        data[index / entriesPerLong] |= static_cast<uint64_t>(value) << bitOffset;
    }
    for (uint64_t word : data) { writer.writeLong(static_cast<int64_t>(word)); }
}

} // namespace

std::vector<std::byte> makeFlatChunkData(World const& world, int32_t chunkX, int32_t chunkZ) {
    net::ByteWriter data;
    for (int section = 0; section < 24; ++section) {
        std::array<int32_t, 4096> blockStates{};
        size_t blockCount = 0;
        int16_t fluidCount = 0;
        size_t index = 0;
        for (int localY = 0; localY < 16; ++localY) {
            int32_t worldY = -64 + section * 16 + localY;
            for (int localZ = 0; localZ < 16; ++localZ) {
                int32_t worldZ = chunkZ * 16 + localZ;
                for (int localX = 0; localX < 16; ++localX, ++index) {
                    int32_t worldX = chunkX * 16 + localX;
                    blockStates[index] = world.blockStateAt({worldX, worldY, worldZ});
                    blockCount += world.isAirState(blockStates[index]) ? 0 : 1;
                    fluidCount += world.isFluidState(blockStates[index]) ? 1 : 0;
                }
            }
        }
        data.writeShort(static_cast<int16_t>(blockCount));
        data.writeShort(fluidCount);
        writePalettedContainer(data, blockStates, blockCount, world.globalBlockStateBits());
        std::array<int32_t, 64> biomes{};
        for (int y = 0; y < 4; ++y) {
            for (int z = 0; z < 4; ++z) {
                for (int x = 0; x < 4; ++x) {
                    biomes[y * 16 + z * 4 + x] = world.biomeAt(chunkX * 16 + x * 4, -64 + section * 16 + y * 4, chunkZ * 16 + z * 4);
                }
            }
        }
        writePalettedContainer(data, biomes, 64, world.globalBiomeBits(), 1, 3);
    }
    return data.take();
}

} // namespace mcserver::server
