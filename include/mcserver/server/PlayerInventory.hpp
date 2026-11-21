#pragma once

#include <array>
#include <cstdint>

namespace mcserver::server {

struct InventorySlot {
    int32_t itemId = 0;
    int32_t count = 0;

    [[nodiscard]] bool empty() const noexcept { return itemId == 0 || count == 0; }
};

struct PlayerInventory {
    std::array<InventorySlot, 9> hotbar{};
    std::array<InventorySlot, 27> main{};
    std::array<InventorySlot, 4> armor{};
    InventorySlot offhand{};
    int16_t selectedHotbarSlot = 0;

    PlayerInventory();
};

struct PlayerPosition {
    double x = 0.5;
    double y = 1.0;
    double z = 0.5;
    float yaw = 0.0f;
    float pitch = 0.0f;
    bool onGround = true;
    bool saved = false;
};

struct PlayerProfile {
    PlayerInventory inventory;
    PlayerPosition position;
};

} // namespace mcserver::server
