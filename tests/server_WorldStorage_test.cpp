#include "mcserver/server/WorldStorage.hpp"

#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

#include <atomic>
#include <chrono>
#include <fstream>

using mcserver::server::World;
using mcserver::server::WorldStorage;
using Json = nlohmann::json;

namespace {
struct SaveFixture {
    std::filesystem::path directory;
    std::filesystem::path file;
    SaveFixture() {
        static std::atomic<unsigned> next{0};
        directory = std::filesystem::temp_directory_path() /
            ("mcserver-storage-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) +
             "-" + std::to_string(next++));
        std::filesystem::create_directory(directory);
        file = directory / "nested" / "world.json";
    }
    ~SaveFixture() {
        std::error_code ignored;
        std::filesystem::remove_all(directory, ignored);
    }
    void write(std::string const& contents) const {
        std::filesystem::create_directories(file.parent_path());
        std::ofstream(file) << contents;
    }
    std::string read() const {
        std::ifstream input(file);
        return std::string(std::istreambuf_iterator<char>(input), {});
    }
};
Json document(Json blocks = Json::array()) {
    return {{"version", 1}, {"world", "flat-stone-v1"}, {"broken_blocks", std::move(blocks)}};
}
} // namespace

TEST_CASE("A missing save starts a new world without creating a file", "[storage]") {
    SaveFixture fixture;
    WorldStorage storage(fixture.file);
    World world;
    REQUIRE_FALSE(storage.load(world));
    REQUIRE(world.blockStateAt({0, 0, 0}) == 1);
    REQUIRE_FALSE(std::filesystem::exists(fixture.file));
}

TEST_CASE("World saves round trip and replace older snapshots", "[storage]") {
    SaveFixture fixture;
    WorldStorage storage(fixture.file);
    World world;
    world.setBlockToAir({-16, 0, -16});
    world.setBlockToAir({31, 0, 31});
    storage.save(world);
    World restored;
    REQUIRE(storage.load(restored));
    REQUIRE(restored.blockChanges().size() == 2);
    REQUIRE(restored.blockStateAt({-16, 0, -16}) == 0);
    REQUIRE(restored.blockStateAt({31, 0, 31}) == 0);
    REQUIRE(restored.blockStateAt({0, 0, 0}) == 1);
    restored.setBlockToAir({0, 0, 0});
    storage.save(restored);
    REQUIRE(storage.load(world));
    REQUIRE(world.blockChanges().size() == 3);
    REQUIRE_FALSE(std::filesystem::exists(fixture.file.string() + ".tmp"));
    REQUIRE(Json::parse(fixture.read()).at("version") == 2);
    storage.save(World{});
    REQUIRE(storage.load(world));
    REQUIRE(world.blockChanges().empty());
}

TEST_CASE("Corrupt and incompatible saves preserve both memory and source bytes", "[storage]") {
    SaveFixture fixture;
    WorldStorage storage(fixture.file);
    World world;
    world.setBlockToAir({5, 0, 5});
    std::vector<std::string> invalid = {
        "{bad json", "null", "[]", "{}",
        R"({"version":2,"world":"flat-stone-v1","broken_blocks":[]})",
        R"({"version":1.0,"world":"flat-stone-v1","broken_blocks":[]})",
        R"({"version":1,"world":"another-world","broken_blocks":[]})",
        R"({"version":1,"world":"flat-stone-v1","broken_blocks":{}})"
    };
    for (auto const& bytes : invalid) {
        fixture.write(bytes);
        REQUIRE_THROWS(storage.load(world));
        REQUIRE(fixture.read() == bytes);
        REQUIRE(world.blockChanges().size() == 1);
        REQUIRE(world.blockStateAt({5, 0, 5}) == 0);
    }
}

TEST_CASE("Save loading rejects invalid coordinates and duplicates transactionally", "[storage]") {
    SaveFixture fixture;
    WorldStorage storage(fixture.file);
    World world;
    world.setBlockToAir({5, 0, 5});
    for (auto block : std::vector<Json>{
        {{"x", -17}, {"y", 0}, {"z", 0}}, {{"x", 32}, {"y", 0}, {"z", 0}},
        {{"x", 0}, {"y", 1}, {"z", 0}}, {{"x", 0}, {"y", 0}, {"z", 32}},
        {{"x", 0.5}, {"y", 0}, {"z", 0}}, {{"x", "0"}, {"y", 0}, {"z", 0}},
        {{"x", true}, {"y", 0}, {"z", 0}}, {{"x", 0}, {"y", 0}},
        {{"x", 18446744073709551615ULL}, {"y", 0}, {"z", 0}},
        {{"x", -9223372036854775807LL}, {"y", 0}, {"z", 0}}}) {
        auto bytes = document(Json::array({{{"x", 1}, {"y", 0}, {"z", 1}}, block})).dump();
        fixture.write(bytes);
        REQUIRE_THROWS(storage.load(world));
        REQUIRE(world.blockChanges().size() == 1);
        REQUIRE(world.blockStateAt({1, 0, 1}) == 1);
    }
    Json block{{"x", 0}, {"y", 0}, {"z", 0}};
    fixture.write(document(Json::array({block, block})).dump());
    REQUIRE_THROWS(storage.load(world));
    REQUIRE(world.blockChanges().size() == 1);
}

TEST_CASE("Oversized world saves and block lists are rejected", "[storage]") {
    SaveFixture fixture;
    WorldStorage storage(fixture.file);
    World world;
    fixture.write(std::string(32 * 1024 * 1024 + 1, ' '));
    REQUIRE_THROWS(storage.load(world));
    auto blocks = Json::array();
    for (int index = 0; index < 2305; ++index) { blocks.push_back({{"x", 0}, {"y", 0}, {"z", 0}}); }
    fixture.write(document(blocks).dump());
    REQUIRE_THROWS(storage.load(world));
}

TEST_CASE("Failed writes preserve the last good save and can be retried", "[storage]") {
    SaveFixture fixture;
    WorldStorage storage(fixture.file);
    World world;
    world.setBlockToAir({0, 0, 0});
    storage.save(world);
    auto original = fixture.read();
    auto temporary = std::filesystem::path(fixture.file.string() + ".tmp");
    std::filesystem::create_directory(temporary);
    world.setBlockToAir({1, 0, 0});
    REQUIRE_THROWS(storage.save(world));
    REQUIRE(fixture.read() == original);
    REQUIRE(std::filesystem::is_directory(temporary));
    std::filesystem::remove(temporary);
    REQUIRE_NOTHROW(storage.save(world));
    World restored;
    REQUIRE(storage.load(restored));
    REQUIRE(restored.blockChanges().size() == 2);
}

TEST_CASE("Every modified ground block fits in the save format", "[storage]") {
    SaveFixture fixture;
    WorldStorage storage(fixture.file);
    World world;
    for (int z = -16; z < 32; ++z) {
        for (int x = -16; x < 32; ++x) { world.setBlockToAir({x, 0, z}); }
    }
    storage.save(world);
    World restored;
    REQUIRE(storage.load(restored));
    REQUIRE(restored.blockChanges().size() == 2304);
    REQUIRE(restored.blockStateAt({-1, 0, -1}) == 0);
}

TEST_CASE("Persistence preserves placed states and imports legacy saves", "[storage]") {
    SaveFixture fixture;
    WorldStorage storage(fixture.file);
    World world;
    fixture.write(document(Json::array({{{"x", -1}, {"y", 0}, {"z", -1}}})).dump());
    REQUIRE(storage.load(world));
    REQUIRE(world.blockStateAt({-1, 0, -1}) == 0);
    REQUIRE_FALSE(world.dirty());
    REQUIRE(world.tryPlaceBlock({2, 1, 2}, 1));
    REQUIRE(world.dirty());
    storage.save(world);
    auto saved = Json::parse(fixture.read());
    REQUIRE(saved.at("version") == 2);
    REQUIRE(saved.at("protocol") == 777);
    World restored;
    REQUIRE(storage.load(restored));
    REQUIRE(restored.blockStateAt({2, 1, 2}) == 1);
    REQUIRE(restored.blockStateAt({-1, 0, -1}) == 0);
    restored.setBlockToAir({2, 1, 2});
    REQUIRE(restored.blockChanges().size() == 1);
    storage.save(restored);
    REQUIRE(storage.load(world));
    REQUIRE(world.blockStateAt({2, 1, 2}) == 0);
}

TEST_CASE("Version two rejects invalid block state and preserves current state", "[storage]") {
    SaveFixture fixture;
    WorldStorage storage(fixture.file);
    World world;
    world.setBlockToAir({1, 0, 1});
    for (int state : {-1, 999999999}) {
        Json invalid{{"version", 2}, {"world", "flat-stone-v1"}, {"protocol", 777},
                     {"blocks", Json::array({{{"x", 0}, {"y", 1}, {"z", 0}, {"state", state}}})}};
        fixture.write(invalid.dump());
        REQUIRE_THROWS(storage.load(world));
        REQUIRE(world.blockStateAt({1, 0, 1}) == 0);
    }
}
