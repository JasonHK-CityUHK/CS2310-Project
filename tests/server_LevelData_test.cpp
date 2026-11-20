#include "mcserver/server/LevelData.hpp"

#include <catch2/catch_test_macros.hpp>
#include <nbt/NBT.hpp>
#include <zlib.h>

#include <atomic>
#include <chrono>
#include <fstream>

namespace {

struct LevelFixture {
    std::filesystem::path directory;
    LevelFixture() {
        static std::atomic<unsigned> next{0};
        directory = std::filesystem::temp_directory_path() /
            ("mcserver-level-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) +
             "-" + std::to_string(next++));
        std::filesystem::create_directory(directory);
    }
    ~LevelFixture() {
        std::error_code ignored;
        std::filesystem::remove_all(directory, ignored);
    }
    void write(nbt::CompoundTag const& root) const {
        auto data = root.toBinaryNbt(false);
        gzFile file = gzopen((directory / "level.dat").string().c_str(), "wb");
        REQUIRE(file != nullptr);
        REQUIRE(gzwrite(file, data.data(), static_cast<unsigned>(data.size())) == static_cast<int>(data.size()));
        REQUIRE(gzclose(file) == Z_OK);
    }
};

nbt::CompoundTag level(int version = 5023) {
    nbt::CompoundTag spawn{{"dimension", "minecraft:overworld"}, {"pos", nbt::IntArrayTag({-20, 72, 30})},
                           {"yaw", 90.5f}, {"pitch", -15.25f}};
    nbt::CompoundTag data{{"DataVersion", version}, {"spawn", spawn}, {"LevelName", "Example"}};
    return {{"Data", data}};
}

} // namespace

TEST_CASE("Level data reads gzip metadata and overworld spawn", "[level-data]") {
    LevelFixture fixture;
    fixture.write(level());
    auto metadata = mcserver::server::loadLevelData(fixture.directory);
    REQUIRE(metadata.dataVersion == 5023);
    REQUIRE(metadata.spawnDimension == "minecraft:overworld");
    REQUIRE(metadata.spawnX == -20);
    REQUIRE(metadata.spawnY == 72);
    REQUIRE(metadata.spawnZ == 30);
    REQUIRE(metadata.spawnYaw == 90.5f);
    REQUIRE(metadata.spawnPitch == -15.25f);
}

TEST_CASE("Level data rejects incompatible and corrupt input", "[level-data]") {
    LevelFixture fixture;
    REQUIRE_THROWS(mcserver::server::loadLevelData(fixture.directory));
    fixture.write(level(5022));
    REQUIRE_THROWS(mcserver::server::loadLevelData(fixture.directory));
    auto invalid = level();
    invalid["Data"].as<nbt::CompoundTag>()["spawn"].as<nbt::CompoundTag>()["pos"] = nbt::IntArrayTag({1, 2});
    fixture.write(invalid);
    REQUIRE_THROWS(mcserver::server::loadLevelData(fixture.directory));
    fixture.write(level());
    auto path = fixture.directory / "level.dat";
    std::filesystem::resize_file(path, std::filesystem::file_size(path) - 4);
    REQUIRE_THROWS(mcserver::server::loadLevelData(fixture.directory));
    std::ofstream(fixture.directory / "level.dat", std::ios::binary | std::ios::trunc) << "not gzip";
    REQUIRE_THROWS(mcserver::server::loadLevelData(fixture.directory));
}
