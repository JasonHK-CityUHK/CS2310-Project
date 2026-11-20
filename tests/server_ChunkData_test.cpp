#include "mcserver/net/ByteBuffer.hpp"
#include "mcserver/server/ChunkData.hpp"
#include "mcserver/server/World.hpp"

#include <array>
#include <catch2/catch_test_macros.hpp>
#include <span>
#include <vector>

using namespace mcserver;

namespace {

struct SectionData {
    int16_t blockCount = 0;
    uint8_t bitsPerEntry = 0;
    std::vector<int32_t> palette;
    std::vector<uint64_t> blockData;
};

SectionData readSection(net::ByteReader& reader) {
    SectionData section;
    section.blockCount = reader.readShort();
    REQUIRE(reader.readShort() == 0);
    section.bitsPerEntry = reader.readUByte();

    if (section.bitsPerEntry == 0) {
        section.palette.push_back(reader.readVarInt());
    } else {
        if (section.bitsPerEntry <= 8) {
            int32_t paletteSize = reader.readVarInt();
            for (int32_t index = 0; index < paletteSize; ++index) {
                section.palette.push_back(reader.readVarInt());
            }
        }
        size_t entriesPerLong = 64 / section.bitsPerEntry;
        size_t longCount = (4096 + entriesPerLong - 1) / entriesPerLong;
        section.blockData.reserve(longCount);
        for (size_t index = 0; index < longCount; ++index) {
            section.blockData.push_back(static_cast<uint64_t>(reader.readLong()));
        }
    }

    REQUIRE(reader.readUByte() == 0);
    REQUIRE(reader.readVarInt() == 41);
    return section;
}

SectionData readGroundSection(server::World const& world) {
    auto chunkData = server::makeFlatChunkData(world, 0, 0);
    net::ByteReader reader{std::span<const std::byte>(chunkData)};
    SectionData groundSection;
    for (int section = 0; section <= 4; ++section) {
        groundSection = readSection(reader);
    }
    return groundSection;
}

} // namespace

TEST_CASE("Chunk data reflects broken block state", "[chunk]") {
    server::World world;
    net::BlockPos brokenBlock{.x = 3, .y = 0, .z = 2};

    auto initialSection = readGroundSection(world);
    REQUIRE(initialSection.blockCount == 256);

    world.setBlockToAir(brokenBlock);
    auto updatedSection = readGroundSection(world);
    REQUIRE(updatedSection.blockCount == 255);
    REQUIRE(updatedSection.bitsPerEntry == 4);
    REQUIRE(updatedSection.palette == std::vector<int32_t>{0, 1});

    size_t brokenBlockIndex = 2 * 16 + 3;
    size_t brokenBit = brokenBlockIndex * 4;
    REQUIRE(((updatedSection.blockData[brokenBit / 64] >> (brokenBit % 64)) & 0xF) == 0);

    size_t neighboringBit = (brokenBlockIndex + 1) * 4;
    REQUIRE(((updatedSection.blockData[neighboringBit / 64] >> (neighboringBit % 64)) & 0xF) == 1);
}

TEST_CASE("Chunk data uses the global palette for many placed block states", "[chunk]") {
    server::World world;
    REQUIRE(world.tryPlaceBlock({.x = 0, .y = 1, .z = 0}, 2000));
    for (int32_t index = 0; index < 256; ++index) {
        REQUIRE(world.tryPlaceBlock({.x = index % 16, .y = 2, .z = index / 16}, 2001 + index));
    }

    auto section = readGroundSection(world);
    REQUIRE(section.blockCount == 513);
    REQUIRE(section.bitsPerEntry == world.globalBlockStateBits());
    REQUIRE(section.palette.empty());
    REQUIRE((section.blockData[64] & 0xFFFF) == 2000);
}

TEST_CASE("Java chunk lighting sends empty block light and inherited skylight", "[chunk]") {
    nbt::CompoundTag section{{"Y", static_cast<int8_t>(0)}, {"SkyLight", nbt::ByteArrayTag(std::vector<uint8_t>(2048, 0))}};
    nbt::CompoundTag chunk{{"sections", nbt::ListTag({section})}};
    net::ByteWriter writer;
    server::writeJavaChunkLight(writer, chunk);
    net::ByteReader reader{std::span<const std::byte>(writer.data())};
    auto readMask = [&reader]() {
        uint64_t result = 0;
        int32_t length = reader.readVarInt();
        for (int32_t index = 0; index < length; ++index) { result |= static_cast<uint64_t>(reader.readUByte()) << (index * 8); }
        return result;
    };
    REQUIRE(readMask() == (((uint64_t{1} << 26) - 1) & ~((uint64_t{1} << 6) - 1)));
    REQUIRE(readMask() == 0);
    REQUIRE(readMask() == ((uint64_t{1} << 6) - 1));
    REQUIRE(readMask() == ((uint64_t{1} << 26) - 1));
    REQUIRE(reader.readVarInt() == 20);
    for (int index = 0; index < 20; ++index) {
        REQUIRE(reader.readVarInt() == 2048);
        auto bytes = reader.readByteArray(2048);
        REQUIRE(bytes.front() == std::byte{0xff});
    }
    REQUIRE(reader.readVarInt() == 0);
    REQUIRE(reader.remaining() == 0);
}
