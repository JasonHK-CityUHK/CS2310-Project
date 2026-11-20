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

void writePalettedContainer(net::ByteWriter& writer, std::array<int32_t, 4096> const& blockStates,
                            size_t blockCount, uint8_t globalBitsPerEntry) {
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
        std::max<uint8_t>(4, static_cast<uint8_t>(std::bit_width(palette.size() - 1)));
    bool useGlobalPalette = bitsPerEntry > 8;
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

void writeBiomes(net::ByteWriter& writer, std::array<int32_t, 64> const& biomes, uint8_t globalBits) {
    std::vector<int32_t> palette;
    std::unordered_map<int32_t, uint32_t> indices;
    for (auto biome : biomes) {
        if (!indices.contains(biome)) {
            indices.emplace(biome, static_cast<uint32_t>(palette.size()));
            palette.push_back(biome);
        }
    }
    if (palette.size() == 1) {
        writer.writeUByte(0);
        writer.writeVarInt(palette.front());
        return;
    }
    uint8_t bits = static_cast<uint8_t>(std::bit_width(palette.size() - 1));
    bool direct = bits > 3;
    if (direct) { bits = globalBits; }
    writer.writeUByte(bits);
    if (!direct) {
        writer.writeVarInt(static_cast<int32_t>(palette.size()));
        for (auto biome : palette) { writer.writeVarInt(biome); }
    }
    size_t perWord = 64 / bits;
    std::vector<uint64_t> words((biomes.size() + perWord - 1) / perWord, 0);
    for (size_t index = 0; index < biomes.size(); ++index) {
        uint32_t value = direct ? static_cast<uint32_t>(biomes[index]) : indices.at(biomes[index]);
        words[index / perWord] |= static_cast<uint64_t>(value) << ((index % perWord) * bits);
    }
    for (auto word : words) { writer.writeLong(static_cast<int64_t>(word)); }
}

} // namespace

std::vector<std::byte> makeFlatChunkData(World const& world, int32_t chunkX, int32_t chunkZ) {
    net::ByteWriter data;
    if (auto* java = world.javaWorld()) {
        auto chunk = java->chunk(chunkX, chunkZ);
        if (!chunk) { throw std::runtime_error("cannot send missing chunk"); }
        for (size_t section = 0; section < chunk->sections.size(); ++section) {
            auto const& states = chunk->sections[section];
            size_t blockCount = 0;
            size_t fluidCount = 0;
            for (auto state : states) {
                blockCount += !java->registry().isAir(state);
                fluidCount += java->registry().hasFluid(state);
            }
            data.writeShort(static_cast<int16_t>(blockCount));
            data.writeShort(static_cast<int16_t>(fluidCount));
            writePalettedContainer(data, states, blockCount, world.globalBlockStateBits());
            writeBiomes(data, chunk->biomes[section], java->biomeBits());
        }
        return data.take();
    }
    for (int section = 0; section < 24; ++section) {
        std::array<int32_t, 4096> blockStates{};
        size_t blockCount = 0;
        size_t index = 0;
        for (int localY = 0; localY < 16; ++localY) {
            int32_t worldY = -64 + section * 16 + localY;
            for (int localZ = 0; localZ < 16; ++localZ) {
                int32_t worldZ = chunkZ * 16 + localZ;
                for (int localX = 0; localX < 16; ++localX, ++index) {
                    int32_t worldX = chunkX * 16 + localX;
                    blockStates[index] = world.blockStateAt({worldX, worldY, worldZ});
                    blockCount += blockStates[index] != 0 ? 1 : 0;
                }
            }
        }
        data.writeShort(static_cast<int16_t>(blockCount));
        data.writeShort(0); // fluid count
        writePalettedContainer(data, blockStates, blockCount, world.globalBlockStateBits());
        data.writeUByte(0); // single-valued biome palette
        data.writeVarInt(41); // plains biome registry ID
    }
    return data.take();
}

void writeJavaChunkLight(net::ByteWriter& writer, nbt::CompoundTag const& chunk) {
    std::array<std::array<uint8_t, 2048>, 26> sky{};
    std::array<std::array<uint8_t, 2048>, 26> block{};
    std::array<bool, 26> skyPresent{};
    if (!chunk.contains("sections", nbt::Tag::Type::List)) { throw std::runtime_error("missing chunk sections"); }
    auto const& sections = chunk.at("sections").as<nbt::ListTag>();
    if (!sections.empty() && sections.getElementType() != nbt::Tag::Type::Compound) {
        throw std::runtime_error("invalid chunk sections");
    }
    for (auto const& sectionTag : sections) {
        auto const& section = sectionTag.as<nbt::CompoundTag>();
        if (!section.contains("Y", nbt::Tag::Type::Byte)) { throw std::runtime_error("missing light section Y"); }
        int sectionY = static_cast<int8_t>(section.at("Y").as<nbt::ByteTag>().storage());
        if (sectionY < -5 || sectionY > 20) { throw std::runtime_error("invalid light section Y"); }
        size_t index = static_cast<size_t>(sectionY + 5);
        for (auto name : {"SkyLight", "BlockLight"}) {
            if (!section.contains(name)) { continue; }
            if (!section.contains(name, nbt::Tag::Type::ByteArray)) { throw std::runtime_error("invalid chunk light array"); }
            auto const& bytes = section.at(name).as<nbt::ByteArrayTag>().storage();
            if (bytes.size() != 2048) { throw std::runtime_error("invalid chunk light array size"); }
            if (std::string_view(name) == "SkyLight") {
                std::copy(bytes.begin(), bytes.end(), sky[index].begin());
                skyPresent[index] = true;
            } else { std::copy(bytes.begin(), bytes.end(), block[index].begin()); }
        }
    }
    for (int index = 25; index >= 0; --index) {
        if (skyPresent[static_cast<size_t>(index)]) { continue; }
        auto& current = sky[static_cast<size_t>(index)];
        if (index == 25) { current.fill(0xff); }
        else {
            auto const& above = sky[static_cast<size_t>(index + 1)];
            for (size_t layer = 0; layer < 16; ++layer) {
                std::copy_n(above.begin(), 128, current.begin() + layer * 128);
            }
        }
    }
    uint64_t skyMask = 0;
    uint64_t blockMask = 0;
    uint64_t emptySky = 0;
    uint64_t emptyBlock = 0;
    for (size_t index = 0; index < 26; ++index) {
        bool hasSky = std::any_of(sky[index].begin(), sky[index].end(), [](uint8_t value) { return value != 0; });
        bool hasBlock = std::any_of(block[index].begin(), block[index].end(), [](uint8_t value) { return value != 0; });
        (hasSky ? skyMask : emptySky) |= uint64_t{1} << index;
        (hasBlock ? blockMask : emptyBlock) |= uint64_t{1} << index;
    }
    auto writeMask = [&writer](uint64_t mask) {
        size_t count = mask == 0 ? 0 : (64 - std::countl_zero(mask) + 7) / 8;
        writer.writeVarInt(static_cast<int32_t>(count));
        for (size_t index = 0; index < count; ++index) { writer.writeUByte(static_cast<uint8_t>(mask >> (index * 8))); }
    };
    writeMask(skyMask);
    writeMask(blockMask);
    writeMask(emptySky);
    writeMask(emptyBlock);
    auto writeArrays = [&writer](auto const& arrays, uint64_t mask) {
        writer.writeVarInt(static_cast<int32_t>(std::popcount(mask)));
        for (size_t index = 0; index < arrays.size(); ++index) {
            if ((mask & (uint64_t{1} << index)) == 0) { continue; }
            writer.writeVarInt(2048);
            for (uint8_t byte : arrays[index]) { writer.writeUByte(byte); }
        }
    };
    writeArrays(sky, skyMask);
    writeArrays(block, blockMask);
}

} // namespace mcserver::server
