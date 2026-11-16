#include "mcserver/server/AnvilWorld.hpp"
#include "mcserver/server/World.hpp"
#include "mcserver/server/WorldStorage.hpp"
#include "mcserver/protocol/JsonToNbt.hpp"

#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>
#include <zlib.h>

#include <chrono>
#include <fstream>
#include <map>

using namespace mcserver;
using Json = nlohmann::json;
namespace {
std::string binary(Json const& value) {
    auto tag = protocol::jsonValueToNbt(value);
    if (value.contains("sections")) {
        for (size_t index = 0; index < value.at("sections").size(); ++index) {
            tag["sections"][index]["Y"] = nbt::ByteTag(static_cast<uint8_t>(value["sections"][index]["Y"].get<int>()));
            auto const& states = value["sections"][index]["block_states"];
            if (states.contains("data")) {
                tag["sections"][index]["block_states"]["data"] = nbt::LongArrayTag(states["data"].get<std::vector<int64_t>>());
            }
        }
    }
    auto bytes = tag.as<nbt::CompoundTag>().toBinaryNbt(false);
    if (value.contains("xPos")) {
        auto decoded = Json::parse(nbt::CompoundTagVariant(nbt::CompoundTag::fromBinaryNbt(bytes, false)).toJson(0));
        REQUIRE(decoded.contains("xPos"));
    }
    return bytes;
}
std::string compress(std::string const& value, bool gzip) {
    z_stream stream{};
    REQUIRE(deflateInit2(&stream, 6, Z_DEFLATED, gzip ? 31 : 15, 8, Z_DEFAULT_STRATEGY) == Z_OK);
    std::string result(compressBound(static_cast<uLong>(value.size())) + 128, '\0');
    stream.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(value.data()));
    stream.avail_in = static_cast<uInt>(value.size());
    stream.next_out = reinterpret_cast<Bytef*>(result.data());
    stream.avail_out = static_cast<uInt>(result.size());
    int code = deflate(&stream, Z_FINISH);
    auto size = stream.total_out;
    deflateEnd(&stream);
    REQUIRE(code == Z_STREAM_END);
    result.resize(size);
    return result;
}
void write(std::filesystem::path const& file, std::string const& value) {
    std::filesystem::create_directories(file.parent_path());
    std::ofstream stream(file, std::ios::binary);
    stream.write(value.data(), static_cast<std::streamsize>(value.size()));
}
void putInt(std::string& bytes, size_t offset, uint32_t value) {
    for (size_t index = 0; index < 4; ++index) { bytes.at(offset + index) = static_cast<char>(value >> ((3-index)*8)); }
}
struct Fixture {
    std::filesystem::path directory;
    explicit Fixture(int version = 5023, bool badIndex = false, bool unknownBlock = false) {
        static unsigned count = 0;
        directory = std::filesystem::temp_directory_path() /
            ("mc-anvil-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) + "-" + std::to_string(count++));
        Json metadata;
        metadata["Data"] = {{"DataVersion", version}, {"LevelName", "Fixture"}};
        metadata["Data"]["spawn"] = {{"dimension", "minecraft:overworld"}, {"pos", {-1,70,0}}};
        write(directory / "level.dat", compress(binary(metadata), true));
        std::map<std::pair<int,int>, std::string> regions;
        for (int z = -1; z <= 1; ++z) {
            for (int x = -2; x <= 0; ++x) {
                Json sections = Json::array();
                for (int y = -4; y < 20; ++y) {
                    Json states{{"palette", Json::array({"minecraft:air"})}};
                    if (y == 0) {
                        states["palette"] = Json::array({Json{{"", unknownBlock ? "minecraft:missing" : "minecraft:stone"}},
                            {{"id", "minecraft:oak_stairs"}, {"properties", {{"facing", "west"}, {"half", "bottom"},
                               {"shape", "straight"}, {"waterlogged", "false"}}}}});
                        std::vector<int64_t> data(256, 0);
                        // Local x=15 at y=z=0: the high nibble exercises signed NBT longs.
                        data[0] = static_cast<int64_t>((badIndex ? uint64_t{15} : uint64_t{1}) << 60);
                        states["data"] = data;
                    }
                    sections.push_back({{"Y",y}, {"block_states", states},
                        {"biomes", {{"palette", Json::array({"minecraft:plains"})}}}});
                }
                auto bytes = binary(Json{{"DataVersion",5023},{"xPos",x},{"zPos",z},
                                         {"Status","minecraft:full"},{"sections",sections}});
                int compression = x == -2 ? 1 : x == -1 ? 2 : 3;
                if (compression != 3) { bytes = compress(bytes, compression == 1); }
                int rx = server::AnvilWorld::floorDiv(x,32), rz = server::AnvilWorld::floorDiv(z,32);
                auto& region = regions[{rx,rz}];
                if (region.empty()) { region.resize(8192, '\0'); }
                auto offset = region.size();
                auto sectorCount = (bytes.size() + 5 + 4095) / 4096;
                region.resize(offset + sectorCount * 4096, '\0');
                putInt(region, static_cast<size_t>((x-rx*32)+(z-rz*32)*32)*4,
                       static_cast<uint32_t>(((offset/4096)<<8)|sectorCount));
                putInt(region, offset, static_cast<uint32_t>(bytes.size()+1));
                region[offset+4] = static_cast<char>(compression);
                region.replace(offset+5, bytes.size(), bytes);
            }
        }
        for (auto const& [position, bytes] : regions) {
            write(directory / "dimensions/minecraft/overworld/region" /
                  ("r."+std::to_string(position.first)+"."+std::to_string(position.second)+".mca"), bytes);
        }
    }
    ~Fixture() { std::error_code ignored; std::filesystem::remove_all(directory, ignored); }
};
}

TEST_CASE("Anvil coordinates use floor division across negative boundaries", "[anvil]") {
    REQUIRE(server::AnvilWorld::floorDiv(-1,16) == -1);
    REQUIRE(server::AnvilWorld::floorDiv(-16,16) == -1);
    REQUIRE(server::AnvilWorld::floorDiv(-17,16) == -2);
    REQUIRE(server::AnvilWorld::floorDiv(-1,32) == -1);
}

TEST_CASE("Anvil reads gzip zlib and raw chunks including signed section Y", "[anvil]") {
    Fixture fixture;
    server::AnvilWorld world(fixture.directory,
        [](std::string const& name, server::AnvilWorld::Properties const& properties) {
            if (name == "minecraft:air") { return 0; }
            if (name == "minecraft:stone") { return 1; }
            REQUIRE(name == "minecraft:oak_stairs");
            REQUIRE(properties.at("facing") == "west");
            REQUIRE(properties.at("waterlogged") == "false");
            return 1234;
        }, [](std::string const& biome) { REQUIRE(biome == "minecraft:plains"); return 7; });
    REQUIRE(world.name() == "Fixture");
    REQUIRE(world.spawn().x == -0.5);
    REQUIRE(world.blockStateAt({-1,0,0}) == 1234);
    REQUIRE(world.blockStateAt({-2,0,0}) == 1);
    REQUIRE(world.blockStateAt({-1,-64,0}) == 0);
    REQUIRE(world.biomeAt(-1,-64,0) == 7);
    REQUIRE(world.contains({-32,0,-16}));
    REQUIRE_FALSE(world.contains({-33,0,-16}));
    REQUIRE(world.identity().starts_with("anvil-5023:"));
}

TEST_CASE("Imported terrain keeps edits above the original terrain across reloads", "[anvil][storage]") {
    Fixture fixture;
    server::World world;
    world.loadAnvil(fixture.directory);
    REQUIRE(world.blockStateAt({-2,10,0}) == 1); // terrain well above the former y=0 plane
    world.setBlockToAir({-2,10,0});
    REQUIRE(world.blockStateAt({-2,10,0}) == 0);
    REQUIRE(world.blockChanges().size() == 1);
    REQUIRE(world.tryPlaceBlock({-2,70,0},1));
    server::WorldStorage storage(fixture.directory / "edits.json");
    storage.save(world);
    world.loadAnvil(fixture.directory);
    REQUIRE(world.blockStateAt({-2,10,0}) == 1);
    REQUIRE(storage.load(world));
    REQUIRE(world.blockStateAt({-2,10,0}) == 0);
    REQUIRE(world.blockStateAt({-2,70,0}) == 1);
    REQUIRE(world.tryPlaceBlock({-2,10,0},1));
    REQUIRE(world.blockChanges().size() == 1); // restoring the original block clears its override
    server::World flat;
    REQUIRE_THROWS(storage.load(flat));
    REQUIRE(flat.blockStateAt({0,0,0}) == 1);
}

TEST_CASE("Invalid Anvil imports fail without replacing the current world", "[anvil]") {
    server::World world;
    for (int scenario = 0; scenario < 3; ++scenario) {
        Fixture fixture(scenario == 0 ? 5000 : 5023, scenario == 1, scenario == 2);
        REQUIRE_THROWS(world.loadAnvil(fixture.directory));
        REQUIRE_FALSE(world.imported());
        REQUIRE(world.blockStateAt({0,0,0}) == 1);
    }
    Fixture fixture;
    auto file = fixture.directory / "dimensions/minecraft/overworld/region/r.-1.-1.mca";
    write(file, std::string(8192, '\0'));
    REQUIRE_THROWS(world.loadAnvil(fixture.directory));
    REQUIRE_FALSE(world.imported());
}
