#pragma once

#include <cstdint>
#include <filesystem>
#include <string>

namespace mcserver::server {

struct LevelData {
    int32_t dataVersion;
    std::string spawnDimension;
    int32_t spawnX;
    int32_t spawnY;
    int32_t spawnZ;
    float spawnYaw;
    float spawnPitch;
};

[[nodiscard]] LevelData loadLevelData(std::filesystem::path const& worldDirectory);

} // namespace mcserver::server
