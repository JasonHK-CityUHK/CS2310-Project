#include "mcserver/server/PlayerInventoryStorage.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace mcserver::server {
namespace {
using Json = nlohmann::json;

InventorySlot readSlot(Json const& value) {
    if (!value.is_object()) { throw std::runtime_error("invalid inventory slot"); }
    int32_t itemId = value.value("item", 0);
    int32_t count = value.value("count", 0);
    if (itemId < 0 || count < 0 || count > 64) {
        throw std::runtime_error("invalid inventory slot value");
    }
    return {.itemId = itemId, .count = itemId == 0 ? 0 : count};
}

Json writeSlot(InventorySlot const& slot) {
    return {{"item", slot.itemId}, {"count", slot.empty() ? 0 : slot.count}};
}
}

PlayerInventoryStorage::PlayerInventoryStorage(std::filesystem::path worldDirectory)
    : worldDirectory_(std::move(worldDirectory)) {}

std::filesystem::path PlayerInventoryStorage::playerFile(
    std::array<std::byte, 16> const& uuid) const {
    std::ostringstream name;
    name << std::hex << std::setfill('0');
    for (std::byte byte : uuid) {
        name << std::setw(2) << static_cast<unsigned int>(std::to_integer<uint8_t>(byte));
    }
    name << ".json";
    return worldDirectory_ / "playerdata" / name.str();
}

bool PlayerInventoryStorage::load(std::array<std::byte, 16> const& uuid,
                                  PlayerInventory& inventory) const {
    PlayerProfile profile;
    if (!load(uuid, profile)) { return false; }
    inventory = profile.inventory;
    return true;
}

bool PlayerInventoryStorage::load(std::array<std::byte, 16> const& uuid,
                                  PlayerProfile& profile) const {
    auto path = playerFile(uuid);
    if (!std::filesystem::exists(path)) { return false; }
    if (std::filesystem::file_size(path) > 1024 * 1024) {
        throw std::runtime_error("player inventory save exceeds 1 MiB");
    }

    std::ifstream input(path, std::ios::binary);
    if (!input) { throw std::runtime_error("cannot read player inventory: " + path.string()); }

    Json document = Json::parse(input);
    if (!document.is_object() || document.value("version", 0) != 1 ||
        document.value("protocol", 0) != 777) {
        throw std::runtime_error("unsupported player inventory format: " + path.string());
    }

    int32_t selected = document.value("selected_hotbar_slot", 0);
    if (selected < 0 || selected >= static_cast<int32_t>(profile.inventory.hotbar.size())) {
        throw std::runtime_error("invalid selected hotbar slot: " + path.string());
    }

    auto const& hotbar = document.at("hotbar");
    if (!hotbar.is_array() || hotbar.size() != profile.inventory.hotbar.size()) {
        throw std::runtime_error("invalid hotbar inventory: " + path.string());
    }
    profile.inventory.selectedHotbarSlot = static_cast<int16_t>(selected);
    for (size_t index = 0; index < profile.inventory.hotbar.size(); ++index) {
        profile.inventory.hotbar[index] = readSlot(hotbar[index]);
    }
    profile.inventory.offhand = readSlot(document.at("offhand"));

    if (document.contains("main") && document.at("main").is_array()) {
        auto const& main = document.at("main");
        if (main.size() != profile.inventory.main.size()) {
            throw std::runtime_error("invalid main inventory: " + path.string());
        }
        for (size_t index = 0; index < main.size(); ++index) {
            profile.inventory.main[index] = readSlot(main[index]);
        }
    }
    if (document.contains("armor") && document.at("armor").is_array()) {
        auto const& armor = document.at("armor");
        if (armor.size() != profile.inventory.armor.size()) {
            throw std::runtime_error("invalid armor inventory: " + path.string());
        }
        for (size_t index = 0; index < armor.size(); ++index) {
            profile.inventory.armor[index] = readSlot(armor[index]);
        }
    }

    if (document.contains("position") && document.at("position").is_object()) {
        auto const& position = document.at("position");
        profile.position.x = position.value("x", 0.5);
        profile.position.y = position.value("y", 1.0);
        profile.position.z = position.value("z", 0.5);
        profile.position.yaw = position.value("yaw", 0.0f);
        profile.position.pitch = position.value("pitch", 0.0f);
        profile.position.onGround = position.value("onGround", true);
        profile.position.saved = position.value("saved", true);
    }
    if (input.bad()) { throw std::runtime_error("error reading player inventory: " + path.string()); }
    return true;
}

void PlayerInventoryStorage::save(std::array<std::byte, 16> const& uuid,
                                  PlayerInventory const& inventory) const {
    PlayerProfile profile;
    profile.inventory = inventory;
    save(uuid, profile);
}

void PlayerInventoryStorage::save(std::array<std::byte, 16> const& uuid,
                                  PlayerProfile const& profile) const {
    auto const& inventory = profile.inventory;
    Json hotbar = Json::array();
    for (auto const& slot : inventory.hotbar) { hotbar.push_back(writeSlot(slot)); }
    Json main = Json::array();
    for (auto const& slot : inventory.main) { main.push_back(writeSlot(slot)); }
    Json armor = Json::array();
    for (auto const& slot : inventory.armor) { armor.push_back(writeSlot(slot)); }

    Json document{
        {"version", 1},
        {"protocol", 777},
        {"selected_hotbar_slot", inventory.selectedHotbarSlot},
        {"hotbar", std::move(hotbar)},
        {"main", std::move(main)},
        {"armor", std::move(armor)},
        {"offhand", writeSlot(inventory.offhand)},
        {"position", {
            {"x", profile.position.x},
            {"y", profile.position.y},
            {"z", profile.position.z},
            {"yaw", profile.position.yaw},
            {"pitch", profile.position.pitch},
            {"onGround", profile.position.onGround},
            {"saved", profile.position.saved},
        }},
    };

    std::filesystem::create_directories(worldDirectory_ / "playerdata");
    auto destination = playerFile(uuid);
    auto temporary = destination;
    temporary += ".tmp";
    std::ofstream output;
    try {
        output.exceptions(std::ios::failbit | std::ios::badbit);
        output.open(temporary, std::ios::binary | std::ios::trunc);
        output << document.dump(2) << '\n';
        output.flush();
        output.close();
        std::filesystem::rename(temporary, destination);
    } catch (...) {
        std::error_code ignored;
        std::filesystem::remove(temporary, ignored);
        throw;
    }
}

} // namespace mcserver::server
