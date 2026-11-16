#pragma once

#include "mcserver/net/ByteBuffer.hpp"

#include <array>
#include <filesystem>
#include <functional>
#include <map>
#include <string>
#include <unordered_map>

namespace mcserver::server {

class AnvilWorld {
public:
    struct Spawn { double x = 0.5, y = 80.0, z = 0.5; float yaw = 0, pitch = 0; };
    using Properties = std::map<std::string, std::string>;
    using BlockResolver = std::function<int32_t(std::string const&, Properties const&)>;
    using BiomeResolver = std::function<int32_t(std::string const&)>;

    AnvilWorld(std::filesystem::path const& directory, BlockResolver resolveBlock, BiomeResolver resolveBiome);
    [[nodiscard]] int32_t blockStateAt(net::BlockPos const& position) const;
    [[nodiscard]] int32_t biomeAt(int32_t x, int32_t y, int32_t z) const;
    [[nodiscard]] bool contains(net::BlockPos const& position) const;
    [[nodiscard]] Spawn const& spawn() const { return spawn_; }
    [[nodiscard]] std::string const& name() const { return name_; }
    [[nodiscard]] std::string const& identity() const { return identity_; }
    static int32_t floorDiv(int32_t value, int32_t divisor);

private:
    struct Chunk {
        std::array<int32_t, 24 * 4096> blocks{};
        std::array<int32_t, 24 * 64> biomes{};
    };
    static uint64_t key(int32_t x, int32_t z);
    std::unordered_map<uint64_t, Chunk> chunks_;
    Spawn spawn_;
    std::string name_, identity_;
};

} // namespace mcserver::server
