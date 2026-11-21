#include "mcserver/server/PlayerInventoryStorage.hpp"

#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <fstream>
#include <chrono>

namespace {

struct InventoryFixture {
    std::filesystem::path directory;
    InventoryFixture()
        : directory(std::filesystem::temp_directory_path() /
                    ("mcserver-inventory-" +
                     std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()))) {
        std::filesystem::create_directories(directory);
    }
    ~InventoryFixture() { std::filesystem::remove_all(directory); }
};

}

TEST_CASE("Player inventory saves and restores by offline UUID", "[player-inventory]") {
    InventoryFixture fixture;
    mcserver::server::PlayerInventoryStorage storage(fixture.directory);
    std::array<std::byte, 16> uuid{};
    for (size_t index = 0; index < uuid.size(); ++index) {
        uuid[index] = static_cast<std::byte>(index);
    }

    mcserver::server::PlayerInventory inventory;
    inventory.hotbar[0] = {.itemId = 42, .count = 17};
    inventory.hotbar[3] = {.itemId = 99, .count = 64};
    inventory.main[4] = {.itemId = 123, .count = 32};
    inventory.armor[1] = {.itemId = 456, .count = 1};
    inventory.offhand = {.itemId = 7, .count = 1};
    inventory.selectedHotbarSlot = 3;
    mcserver::server::PlayerProfile profile;
    profile.inventory = inventory;
    profile.position = {.x = 12.5, .y = 70.0, .z = -8.25,
                        .yaw = 90.0f, .pitch = -20.0f,
                        .onGround = true, .saved = true};
    storage.save(uuid, profile);

    mcserver::server::PlayerProfile restored;
    REQUIRE(storage.load(uuid, restored));
    REQUIRE(restored.inventory.hotbar[0].itemId == 42);
    REQUIRE(restored.inventory.hotbar[0].count == 17);
    REQUIRE(restored.inventory.hotbar[3].itemId == 99);
    REQUIRE(restored.inventory.main[4].itemId == 123);
    REQUIRE(restored.inventory.armor[1].itemId == 456);
    REQUIRE(restored.inventory.offhand.itemId == 7);
    REQUIRE(restored.inventory.selectedHotbarSlot == 3);
    REQUIRE(restored.position.saved);
    REQUIRE(restored.position.x == 12.5);
    REQUIRE(restored.position.y == 70.0);
    REQUIRE(restored.position.z == -8.25);
}

TEST_CASE("Missing player inventory starts with the default inventory", "[player-inventory]") {
    InventoryFixture fixture;
    mcserver::server::PlayerInventoryStorage storage(fixture.directory);
    std::array<std::byte, 16> uuid{};

    mcserver::server::PlayerInventory inventory;
    REQUIRE_FALSE(storage.load(uuid, inventory));
    REQUIRE(inventory.hotbar[0].itemId == 1);
    REQUIRE(inventory.hotbar[0].count == 64);
}

TEST_CASE("Corrupt player inventory rejects startup use", "[player-inventory]") {
    InventoryFixture fixture;
    mcserver::server::PlayerInventoryStorage storage(fixture.directory);
    std::array<std::byte, 16> uuid{};

    auto path = fixture.directory / "playerdata";
    std::filesystem::create_directories(path);
    std::ofstream output(path / "00000000000000000000000000000000.json",
                         std::ios::binary);
    output << "{\"version\":999}";
    output.close();

    mcserver::server::PlayerInventory inventory;
    REQUIRE_THROWS(storage.load(uuid, inventory));
}
