#pragma once

#include "mcserver/server/PlayerInventory.hpp"

#include <array>
#include <cstddef>
#include <filesystem>

namespace mcserver::server {

class PlayerInventoryStorage {
public:
    explicit PlayerInventoryStorage(std::filesystem::path worldDirectory);

    [[nodiscard]] bool load(std::array<std::byte, 16> const& uuid,
                            PlayerInventory& inventory) const;
    void save(std::array<std::byte, 16> const& uuid,
              PlayerInventory const& inventory) const;
    [[nodiscard]] bool load(std::array<std::byte, 16> const& uuid,
                            PlayerProfile& profile) const;
    void save(std::array<std::byte, 16> const& uuid,
              PlayerProfile const& profile) const;

private:
    [[nodiscard]] std::filesystem::path playerFile(
        std::array<std::byte, 16> const& uuid) const;
    std::filesystem::path worldDirectory_;
};

} // namespace mcserver::server
