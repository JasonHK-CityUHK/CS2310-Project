#pragma once

#include <cstdint>
#include <filesystem>
#include <istream>
#include <string>

namespace mcserver::server {

struct ServerProperties {
    std::string serverIp;
    uint16_t serverPort = 25565;
    int32_t viewDistance = 10;
    std::string motd = "CS2310 minimal MC server";
    std::filesystem::path levelName = "world";
};

[[nodiscard]] ServerProperties parseServerProperties(std::istream& input);
[[nodiscard]] ServerProperties loadServerProperties(std::filesystem::path const& path);

} // namespace mcserver::server
