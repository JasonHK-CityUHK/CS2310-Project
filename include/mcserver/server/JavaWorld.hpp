#pragma once

#include "mcserver/net/ByteBuffer.hpp"
#include "mcserver/server/LevelData.hpp"
#include "mcserver/server/SectionData.hpp"
#include "mcserver/server/WorldLock.hpp"

#include <filesystem>
#include <list>
#include <memory>
#include <optional>
#include <unordered_map>
#include <unordered_set>

namespace mcserver::server {

class JavaWorld {
public:
    struct Chunk {
        nbt::CompoundTag data;
        ChunkSections sections;
        BiomeSections biomes;
        bool external = false;
    };

    explicit JavaWorld(std::filesystem::path const& directory);
    [[nodiscard]] LevelData const& level() const noexcept { return level_; }
    [[nodiscard]] std::shared_ptr<Chunk const> chunk(int32_t chunkX, int32_t chunkZ);
    [[nodiscard]] std::optional<int32_t> blockStateAt(net::BlockPos const& position);
    bool setBlock(net::BlockPos const& position, int32_t state);
    [[nodiscard]] bool dirty() const noexcept { return !dirty_.empty(); }
    [[nodiscard]] BlockStateRegistry const& registry() const noexcept { return registry_; }
    [[nodiscard]] uint8_t biomeBits() const noexcept { return biomeBits_; }
    void save();

private:
    struct CachedChunk {
        std::shared_ptr<Chunk> chunk;
        std::list<uint64_t>::iterator position;
    };

    WorldLock lock_;
    std::filesystem::path directory_;
    LevelData level_;
    BlockStateRegistry registry_;
    std::unordered_map<std::string, int32_t> biomeIds_;
    uint8_t biomeBits_ = 0;
    std::list<uint64_t> recentlyUsed_;
    std::unordered_map<uint64_t, CachedChunk> chunks_;
    std::unordered_set<uint64_t> dirty_;
};

} // namespace mcserver::server
