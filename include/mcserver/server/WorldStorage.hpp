#pragma once

#include "mcserver/server/World.hpp"

#include <filesystem>
#include <utility>

namespace mcserver::server {

// Versioned save format for this project's flat world, not an Anvil save.
class WorldStorage {
public:
    explicit WorldStorage(std::filesystem::path file) : file_(std::move(file)) {}
    // Missing files are a new world. Invalid existing files throw without changing world.
    bool load(World& world) const;
    // Write beside the destination and rename only after a complete, closed write.
    void save(World const& world) const;
    [[nodiscard]] std::filesystem::path const& path() const { return file_; }

private:
    std::filesystem::path file_;
};

} // namespace mcserver::server
