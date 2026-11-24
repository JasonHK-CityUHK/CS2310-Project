#include "mcserver/server/RegionFile.hpp"
#include "mcserver/server/LevelData.hpp"
#include "mcserver/server/JavaWorld.hpp"
#include "mcserver/server/SectionData.hpp"
#include "mcserver/server/WorldLock.hpp"
#include "mcserver/server/World.hpp"
#include "mcserver/server/ChunkData.hpp"

#include <catch2/catch_test_macros.hpp>
#include <zlib.h>
#include <lz4.h>
#define XXH_NAMESPACE MCSERVER_
#include <xxhash.h>

#include <atomic>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <utility>

namespace {

struct RegionFixture {
    std::filesystem::path directory;
    std::filesystem::path region;
    RegionFixture() {
        static std::atomic<unsigned> next{0};
        directory = std::filesystem::temp_directory_path() /
            ("mcserver-region-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) +
             "-" + std::to_string(next++));
        region = directory / "dimensions/minecraft/overworld/region";
        std::filesystem::create_directories(region);
    }
    ~RegionFixture() {
        std::error_code ignored;
        std::filesystem::remove_all(directory, ignored);
    }
    void write(std::string const& filename, std::string const& data) const {
        std::ofstream output(region / filename, std::ios::binary);
        output.write(data.data(), static_cast<std::streamsize>(data.size()));
    }
    void writeLevel(std::string const& dimension = "minecraft:overworld") const {
        nbt::CompoundTag spawn{{"dimension", dimension}, {"pos", nbt::IntArrayTag({0, 0, 0})},
                               {"yaw", 0.0f}, {"pitch", 0.0f}};
        nbt::CompoundTag root{{"Data", nbt::CompoundTag{{"DataVersion", 5023}, {"spawn", spawn}}}};
        auto level = root.toBinaryNbt(false);
        gzFile file = gzopen((directory / "level.dat").string().c_str(), "wb");
        REQUIRE(file != nullptr);
        REQUIRE(gzwrite(file, level.data(), static_cast<unsigned>(level.size())) == static_cast<int>(level.size()));
        REQUIRE(gzclose(file) == Z_OK);
    }
};

void setInteger(std::string& data, size_t offset, uint32_t value) {
    for (int index = 0; index < 4; ++index) { data[offset + index] = static_cast<char>(value >> (24 - index * 8)); }
}

std::string regionData(int32_t chunkX, int32_t chunkZ, uint8_t compression = 2) {
    nbt::CompoundTag chunk{{"DataVersion", 5023}, {"xPos", chunkX}, {"zPos", chunkZ}, {"Status", "minecraft:full"},
                           {"sections", nbt::ListTag()}};
    std::string nbt = chunk.toBinaryNbt(false);
    std::string payload = nbt;
    if (compression == 2) {
        uLongf length = compressBound(nbt.size());
        payload.resize(length);
        REQUIRE(compress2(reinterpret_cast<Bytef*>(payload.data()), &length,
                          reinterpret_cast<Bytef const*>(nbt.data()), nbt.size(), Z_DEFAULT_COMPRESSION) == Z_OK);
        payload.resize(length);
    }
    std::string result(3 * 4096, '\0');
    size_t localX = static_cast<uint32_t>(chunkX) & 31;
    size_t localZ = static_cast<uint32_t>(chunkZ) & 31;
    setInteger(result, (localX + localZ * 32) * 4, (2 << 8) | 1);
    setInteger(result, 2 * 4096, static_cast<uint32_t>(payload.size() + 1));
    result[2 * 4096 + 4] = static_cast<char>(compression);
    result.replace(2 * 4096 + 5, payload.size(), payload);
    return result;
}

std::string lz4Stream(std::string const& data, bool compress) {
    std::string payload = data;
    if (compress) {
        payload.resize(static_cast<size_t>(LZ4_compressBound(static_cast<int>(data.size()))));
        int size = LZ4_compress_default(data.data(), payload.data(), static_cast<int>(data.size()),
                                        static_cast<int>(payload.size()));
        REQUIRE(size > 0);
        payload.resize(static_cast<size_t>(size));
    }
    auto littleInteger = [](uint32_t value) {
        std::string bytes(4, '\0');
        for (size_t index = 0; index < 4; ++index) { bytes[index] = static_cast<char>(value >> (index * 8)); }
        return bytes;
    };
    std::string result = "LZ4Block";
    result.push_back(static_cast<char>(compress ? 0x26 : 0x16));
    result += littleInteger(static_cast<uint32_t>(payload.size()));
    result += littleInteger(static_cast<uint32_t>(data.size()));
    result += littleInteger(XXH32(data.data(), data.size(), 0x9747b28c) & 0x0fffffffu);
    result += payload;
    result += "LZ4Block";
    result.push_back(0x16);
    result.append(12, '\0');
    return result;
}

} // namespace

TEST_CASE("Region reader loads existing chunks including negative coordinates", "[region]") {
    RegionFixture fixture;
    REQUIRE_FALSE(mcserver::server::loadRegionChunk(fixture.directory, -1, -1));
    fixture.write("r.-1.-1.mca", regionData(-1, -1));
    auto chunk = mcserver::server::loadRegionChunk(fixture.directory, -1, -1);
    REQUIRE(chunk);
    REQUIRE(static_cast<int32_t>(chunk->at("xPos")) == -1);
    REQUIRE_FALSE(mcserver::server::loadRegionChunk(fixture.directory, -2, -1));
    fixture.write("r.0.0.mca", regionData(0, 0, 3));
    REQUIRE(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
    fixture.write("r.-2.0.mca", regionData(-33, 0));
    REQUIRE(mcserver::server::loadRegionChunk(fixture.directory, -33, 0));
}

TEST_CASE("Region reader rejects corrupted sectors and chunk metadata", "[region]") {
    RegionFixture fixture;
    auto data = regionData(0, 0);
    setInteger(data, 4, (2 << 8) | 1);
    fixture.write("r.0.0.mca", data);
    REQUIRE_THROWS(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
    data = regionData(0, 0);
    setInteger(data, 0, (3 << 8) | 1);
    fixture.write("r.0.0.mca", data);
    REQUIRE_THROWS(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
    data = regionData(0, 0);
    setInteger(data, 2 * 4096, 4096);
    fixture.write("r.0.0.mca", data);
    REQUIRE_THROWS(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
    data = regionData(1, 0);
    setInteger(data, 0, (2 << 8) | 1);
    setInteger(data, 4, 0);
    fixture.write("r.0.0.mca", data);
    REQUIRE_THROWS(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
    data = regionData(0, 0);
    data[2 * 4096 + 4] = 4;
    fixture.write("r.0.0.mca", data);
    REQUIRE_THROWS(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
    data = regionData(0, 0);
    data[2 * 4096 + 5] = 0;
    fixture.write("r.0.0.mca", data);
    REQUIRE_THROWS(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
}

TEST_CASE("Region reader validates out-of-order sector allocations", "[region]") {
    RegionFixture fixture;
    auto data = regionData(0, 0);
    data.resize(6 * 4096);
    setInteger(data, 4, (4 << 8) | 1);
    setInteger(data, 8, (3 << 8) | 1);
    fixture.write("r.0.0.mca", data);
    REQUIRE(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));

    setInteger(data, 4, (4 << 8) | 2);
    setInteger(data, 8, (3 << 8) | 2);
    fixture.write("r.0.0.mca", data);
    REQUIRE_THROWS(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
}

TEST_CASE("Region reader handles gzip and external chunks", "[region]") {
    RegionFixture fixture;
    auto uncompressed = regionData(0, 0, 3);
    uint32_t originalLength = 0;
    for (size_t index = 0; index < 4; ++index) {
        originalLength = (originalLength << 8) | static_cast<uint8_t>(uncompressed[2 * 4096 + index]);
    }
    std::string source = uncompressed.substr(2 * 4096 + 5, originalLength - 1);
    std::string compressed(4096, '\0');
    z_stream stream{};
    REQUIRE(deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 31, 8, Z_DEFAULT_STRATEGY) == Z_OK);
    stream.next_in = reinterpret_cast<Bytef*>(source.data());
    stream.avail_in = static_cast<uInt>(source.size());
    stream.next_out = reinterpret_cast<Bytef*>(compressed.data());
    stream.avail_out = static_cast<uInt>(compressed.size());
    REQUIRE(deflate(&stream, Z_FINISH) == Z_STREAM_END);
    compressed.resize(stream.total_out);
    REQUIRE(deflateEnd(&stream) == Z_OK);
    auto data = uncompressed;
    setInteger(data, 2 * 4096, static_cast<uint32_t>(compressed.size() + 1));
    data[2 * 4096 + 4] = 1;
    data.replace(2 * 4096 + 5, compressed.size(), compressed);
    fixture.write("r.0.0.mca", data);
    REQUIRE(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
    setInteger(data, 2 * 4096, 1);
    data[2 * 4096 + 4] = static_cast<char>(0x81);
    fixture.write("r.0.0.mca", data);
    REQUIRE_THROWS(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
    fixture.write("c.0.0.mcc", compressed);
    REQUIRE(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
    bool external = false;
    REQUIRE(mcserver::server::loadRegionChunk(fixture.directory, 0, 0, &external));
    REQUIRE(external);
    compressed.pop_back();
    fixture.write("c.0.0.mcc", compressed);
    REQUIRE_THROWS(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
}

TEST_CASE("Region reader handles Java LZ4 block streams", "[region]") {
    RegionFixture fixture;
    auto original = regionData(0, 0, 3);
    uint32_t length = 0;
    for (size_t index = 0; index < 4; ++index) {
        length = (length << 8) | static_cast<uint8_t>(original[2 * 4096 + index]);
    }
    auto source = original.substr(2 * 4096 + 5, length - 1);
    for (bool compressed : {false, true}) {
        auto stream = lz4Stream(source, compressed);
        auto region = original;
        setInteger(region, 2 * 4096, static_cast<uint32_t>(stream.size() + 1));
        region[2 * 4096 + 4] = 4;
        region.replace(2 * 4096 + 5, stream.size(), stream);
        fixture.write("r.0.0.mca", region);
        REQUIRE(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
        region[2 * 4096 + 5 + 17] ^= 1;
        fixture.write("r.0.0.mca", region);
        REQUIRE_THROWS(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
        setInteger(region, 2 * 4096, 1);
        region[2 * 4096 + 4] = static_cast<char>(0x84);
        fixture.write("r.0.0.mca", region);
        fixture.write("c.0.0.mcc", stream);
        REQUIRE(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
        stream.pop_back();
        fixture.write("c.0.0.mcc", stream);
        REQUIRE_THROWS(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
    }
}

TEST_CASE("Region writes preserve other chunk records and reject missing chunks", "[region]") {
    RegionFixture fixture;
    mcserver::server::WorldLock lock(fixture.directory);
    auto first = regionData(0, 0);
    auto second = regionData(1, 0);
    setInteger(first, 4, (3 << 8) | 1);
    first.append(second.data() + 2 * 4096, 4096);
    fixture.write("r.0.0.mca", first);
    auto chunk = mcserver::server::loadRegionChunk(fixture.directory, 0, 0);
    REQUIRE(chunk);
    RegionFixture other;
    mcserver::server::WorldLock otherLock(other.directory);
    REQUIRE_THROWS(mcserver::server::saveRegionChunk(otherLock, fixture.directory, 0, 0, *chunk));
    REQUIRE(mcserver::server::loadRegionChunk(fixture.directory, 0, 0)->equals(*chunk));
    (*chunk)["custom"] = 42;
    mcserver::server::saveRegionChunk(lock, fixture.directory, 0, 0, *chunk);
    auto saved = mcserver::server::loadRegionChunk(fixture.directory, 0, 0);
    REQUIRE(saved);
    REQUIRE(static_cast<int32_t>(saved->at("custom")) == 42);
    REQUIRE(mcserver::server::loadRegionChunk(fixture.directory, 1, 0));
    REQUIRE_THROWS(mcserver::server::saveRegionChunk(lock, fixture.directory, 2, 0, *chunk));
    REQUIRE(mcserver::server::loadRegionChunk(fixture.directory, 0, 0));
}

TEST_CASE("Java world reads existing chunks without generating missing ones", "[java-world]") {
    RegionFixture fixture;
    fixture.writeLevel();
    fixture.write("r.0.0.mca", regionData(0, 0));
    fixture.write("r.-1.-1.mca", regionData(-1, -1));
    mcserver::server::JavaWorld world(fixture.directory);
    REQUIRE(world.blockStateAt({0, 0, 0}) == 0);
    REQUIRE(world.blockStateAt({-1, -64, -1}) == 0);
    REQUIRE_FALSE(world.blockStateAt({-17, 0, -17}));
    REQUIRE_FALSE(world.blockStateAt({0, -65, 0}));
    REQUIRE_FALSE(world.chunk(10, 10));
    REQUIRE_FALSE(world.chunk(2097152, 0));
    REQUIRE_FALSE(std::filesystem::exists(fixture.region / "r.0.1.mca"));
}

TEST_CASE("Live world abstraction reads Java chunks", "[java-world]") {
    RegionFixture fixture;
    fixture.writeLevel();
    fixture.write("r.0.0.mca", regionData(0, 0));
    mcserver::server::World world(fixture.directory);
    REQUIRE(world.javaWorld());
    REQUIRE(world.blockStateAt({0, 0, 0}) == 0);
    REQUIRE_THROWS(world.blockStateAt({32, 0, 0}));
    auto packet = mcserver::server::makeFlatChunkData(world, 0, 0);
    mcserver::net::ByteReader reader{std::span<const std::byte>(packet)};
    for (int section = 0; section < 24; ++section) {
        REQUIRE(reader.readShort() == 0);
        REQUIRE(reader.readShort() == 0);
        REQUIRE(reader.readUByte() == 0);
        REQUIRE(reader.readVarInt() == 0);
        REQUIRE(reader.readUByte() == 0);
        REQUIRE(reader.readVarInt() == 41);
    }
}

TEST_CASE("Java-backed world places any registered block into air and persists it", "[java-world]") {
    RegionFixture fixture;
    fixture.writeLevel();
    fixture.write("r.0.0.mca", regionData(0, 0));
    {
        mcserver::server::WorldLock lock(fixture.directory);
        auto chunk = mcserver::server::loadRegionChunk(fixture.directory, 0, 0);
        REQUIRE(chunk);
        nbt::CompoundTag states{{"palette", nbt::ListTag({"minecraft:stone"})}};
        nbt::CompoundTag section{{"Y", static_cast<int8_t>(0)}, {"block_states", states}};
        nbt::CompoundTag airStates{{"palette", nbt::ListTag({"minecraft:air"})}};
        nbt::CompoundTag airSection{{"Y", static_cast<int8_t>(1)}, {"block_states", airStates}};
        nbt::CompoundTag waterStates{{"palette", nbt::ListTag({"minecraft:water"})}};
        nbt::CompoundTag waterSection{{"Y", static_cast<int8_t>(2)}, {"block_states", waterStates}};
        (*chunk)["sections"] = nbt::ListTag({section, airSection, waterSection});
        mcserver::server::saveRegionChunk(lock, fixture.directory, 0, 0, *chunk);
    }
    {
        mcserver::server::World world(fixture.directory);
        REQUIRE(world.blockStateAt({8, 8, 8}) == 1);
        auto packet = mcserver::server::makeFlatChunkData(world, 0, 0);
        mcserver::net::ByteReader reader{std::span<const std::byte>(packet)};
        for (int section = 0; section <= 6; ++section) {
            bool stone = section == 4;
            bool water = section == 6;
            REQUIRE(reader.readShort() == (stone || water ? 4096 : 0));
            REQUIRE(reader.readShort() == (water ? 4096 : 0));
            REQUIRE(reader.readUByte() == 0);
            REQUIRE(reader.readVarInt() == (water ? world.blockStateAt({8, 32, 8}) : stone ? 1 : 0));
            REQUIRE(reader.readUByte() == 0);
            REQUIRE(reader.readVarInt() == 41);
        }
        REQUIRE(world.setBlockToAir({0, 8, 8}));
        world.saveJavaWorld();
        REQUIRE_FALSE(world.dirty());
        auto poiDirectory = fixture.directory / "dimensions/minecraft/overworld/poi";
        std::filesystem::create_directories(poiDirectory);
        {
            std::ofstream poi(poiDirectory / "r.0.0.mca", std::ios::binary);
            auto poiData = regionData(0, 0);
            poi.write(poiData.data(), static_cast<std::streamsize>(poiData.size()));
        }
        REQUIRE_FALSE(world.setBlockToAir({8, 8, 8}));
        REQUIRE_FALSE(world.dirty());
        std::filesystem::remove(poiDirectory / "r.0.0.mca");
        REQUIRE(world.setBlockToAir({8, 8, 8}));
        REQUIRE(world.dirty());
        world.saveJavaWorld();
        REQUIRE_FALSE(world.dirty());
    }
    {
        mcserver::server::World world(fixture.directory);
        REQUIRE(world.blockStateAt({8, 8, 8}) == 0);
        REQUIRE(world.tryPlaceBlock({8, 8, 8}, 1));
        mcserver::server::BlockStateRegistry registry;
        nbt::CompoundTagVariant dirtEntry = nbt::CompoundTag{{"id", "minecraft:dirt"}};
        auto dirtState = registry.resolve(dirtEntry);
        REQUIRE(world.tryPlaceBlock({8, 16, 8}, dirtState));
        REQUIRE(world.blockStateAt({8, 16, 8}) == dirtState);
        REQUIRE_FALSE(world.tryPlaceBlock({8, 16, 8}, 1));
        world.saveJavaWorld();
    }
    {
        mcserver::server::World restored(fixture.directory);
        REQUIRE(restored.blockStateAt({8, 8, 8}) == 1);
        mcserver::server::BlockStateRegistry registry;
        nbt::CompoundTagVariant dirtEntry = nbt::CompoundTag{{"id", "minecraft:dirt"}};
        auto dirtState = registry.resolve(dirtEntry);
        REQUIRE(restored.blockStateAt({8, 16, 8}) == dirtState);
        REQUIRE(restored.setBlockToAir({8, 16, 8}));
        REQUIRE(restored.blockStateAt({8, 16, 8}) == 0);
        restored.saveJavaWorld();
    }
    mcserver::server::World afterBreak(fixture.directory);
    REQUIRE(afterBreak.blockStateAt({8, 16, 8}) == 0);
}

TEST_CASE("Java-backed world places blocks on negative chunk borders and persists them", "[java-world]") {
    for (auto [z, chunkZ] : {std::pair{-65, -5}, std::pair{-64, -4}}) {
        RegionFixture fixture;
        fixture.writeLevel();
        fixture.write("r.0.0.mca", regionData(0, 0));
        fixture.write("r.-1.-1.mca", regionData(-1, chunkZ));
        {
            mcserver::server::WorldLock lock(fixture.directory);
            auto chunk = mcserver::server::loadRegionChunk(fixture.directory, -1, chunkZ);
            REQUIRE(chunk);
            nbt::CompoundTag airStates{{"palette", nbt::ListTag({"minecraft:air"})}};
            nbt::CompoundTag section{{"Y", static_cast<int8_t>(4)}, {"block_states", airStates}};
            (*chunk)["sections"] = nbt::ListTag({section});
            mcserver::server::saveRegionChunk(lock, fixture.directory, -1, chunkZ, *chunk);
        }
        {
            mcserver::server::World world(fixture.directory);
            REQUIRE(world.tryPlaceBlock({-4, 64, z}, 1));
            REQUIRE(world.blockStateAt({-4, 64, z}) == 1);
            world.saveJavaWorld();
        }
        mcserver::server::World restored(fixture.directory);
        REQUIRE(restored.blockStateAt({-4, 64, z}) == 1);
    }
}

TEST_CASE("Java world rejects unsupported or missing spawn chunks", "[java-world]") {
    RegionFixture fixture;
    fixture.writeLevel("minecraft:the_nether");
    REQUIRE_THROWS(mcserver::server::JavaWorld(fixture.directory));
    fixture.writeLevel();
    REQUIRE_THROWS(mcserver::server::JavaWorld(fixture.directory));
    REQUIRE_FALSE(std::filesystem::exists(fixture.region / "r.0.0.mca"));
}

TEST_CASE("Java world evicts cached chunks without invalidating existing handles", "[java-world]") {
    RegionFixture fixture;
    fixture.writeLevel();
    std::string region(2 * 4096, '\0');
    for (int index = 0; index < 70; ++index) {
        auto data = regionData(index % 32, index / 32);
        setInteger(region, static_cast<size_t>(index) * 4, (static_cast<uint32_t>(index + 2) << 8) | 1);
        region.append(data.data() + 2 * 4096, 4096);
    }
    fixture.write("r.0.0.mca", region);
    mcserver::server::JavaWorld world(fixture.directory);
    auto first = world.chunk(0, 0);
    REQUIRE(first);
    for (int index = 1; index < 70; ++index) { REQUIRE(world.chunk(index % 32, index / 32)); }
    REQUIRE(first->sections[0][0] == 0);
    REQUIRE(static_cast<int32_t>(first->data.at("xPos")) == 0);
    REQUIRE(world.chunk(0, 0));
}

TEST_CASE("Region reader loads a supplied 26.3 world", "[sample-world]") {
    auto worldDirectory = std::getenv("MCSERVER_TEST_WORLD_DIR");
    if (!worldDirectory) { SKIP("MCSERVER_TEST_WORLD_DIR is not set"); }
    auto level = mcserver::server::loadLevelData(worldDirectory);
    REQUIRE(level.dataVersion == 5023);
    REQUIRE(level.spawnDimension == "minecraft:overworld");
    int32_t chunkX = level.spawnX / 16 - (level.spawnX % 16 < 0 ? 1 : 0);
    int32_t chunkZ = level.spawnZ / 16 - (level.spawnZ % 16 < 0 ? 1 : 0);
    auto chunk = mcserver::server::loadRegionChunk(worldDirectory, chunkX, chunkZ);
    REQUIRE(chunk);
    REQUIRE(chunk->contains("sections", nbt::Tag::Type::List));
    mcserver::server::BlockStateRegistry registry;
    auto allSections = mcserver::server::decodeChunkSections(*chunk,
        [&registry](auto const& entry) { return registry.resolve(entry); });
    REQUIRE(allSections.size() == 24);
    size_t decodedSections = 0;
    for (auto const& sectionTag : chunk->at("sections").as<nbt::ListTag>()) {
        auto const& section = sectionTag.as<nbt::CompoundTag>();
        if (!section.contains("block_states", nbt::Tag::Type::Compound)) { continue; }
        auto states = mcserver::server::decodeBlockStates(section.at("block_states").as<nbt::CompoundTag>(),
            [&registry](auto const& entry) { return registry.resolve(entry); });
        REQUIRE(states.size() == 4096);
        ++decodedSections;
    }
    REQUIRE(decodedSections > 0);
    {
        mcserver::server::JavaWorld world(worldDirectory);
        REQUIRE(world.level().spawnX == level.spawnX);
        auto block = world.blockStateAt({level.spawnX, level.spawnY, level.spawnZ});
        REQUIRE(block);
        size_t localX = static_cast<size_t>(level.spawnX - chunkX * 16);
        size_t localZ = static_cast<size_t>(level.spawnZ - chunkZ * 16);
        size_t sectionIndex = static_cast<size_t>((level.spawnY + 64) / 16);
        size_t localY = static_cast<size_t>((level.spawnY + 64) % 16);
        REQUIRE(*block == allSections[sectionIndex][localY * 256 + localZ * 16 + localX]);
        REQUIRE_FALSE(world.blockStateAt({0, 320, 0}));
        REQUIRE_FALSE(world.chunk(100000, 100000));
    }
    auto& sections = (*chunk)["sections"].as<nbt::ListTag>();
    bool modified = false;
    for (auto& sectionTag : sections) {
        auto& section = sectionTag.as<nbt::CompoundTag>();
        if (!section.contains("block_states", nbt::Tag::Type::Compound)) { continue; }
        auto states = mcserver::server::decodeBlockStates(section.at("block_states").as<nbt::CompoundTag>(),
            [&registry](auto const& entry) { return registry.resolve(entry); });
        states[0] = states[0] == 1 ? 0 : 1;
        section["block_states"] = mcserver::server::encodeBlockStates(states, registry);
        modified = true;
        break;
    }
    REQUIRE(modified);
    mcserver::server::WorldLock lock(worldDirectory);
    mcserver::server::saveRegionChunk(lock, worldDirectory, chunkX, chunkZ, *chunk);
    auto saved = mcserver::server::loadRegionChunk(worldDirectory, chunkX, chunkZ);
    REQUIRE(saved);
    REQUIRE(saved->equals(*chunk));
}
