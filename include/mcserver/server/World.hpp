#pragma once

#include "mcserver/net/ByteBuffer.hpp"

#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>
#include <unordered_set>

namespace mcserver::net {
class Connection;
}

namespace mcserver::server {

class World {
public:
    World();
    struct BlockChange { net::BlockPos position; int32_t state; };
    [[nodiscard]] std::vector<BlockChange> blockChanges() const;
    void restoreChanges(std::vector<BlockChange> const& changes);
    [[nodiscard]] bool dirty() const noexcept { return dirty_; }
    void markSaved() noexcept { dirty_ = false; }
    [[nodiscard]] bool validBlockState(int32_t state) const { return validBlockStates_.contains(state); }
    static bool contains(net::BlockPos const& position);


    [[nodiscard]] int32_t blockStateAt(net::BlockPos const& position) const;
    void setBlockToAir(net::BlockPos const& position);
    [[nodiscard]] bool tryPlaceBlock(net::BlockPos const& position, int32_t blockState);
    [[nodiscard]] std::optional<int32_t> blockStateForItem(int32_t itemId) const;
    [[nodiscard]] uint8_t globalBlockStateBits() const noexcept { return globalBlockStateBits_; }

    void addPlayer(std::shared_ptr<net::Connection> const& connection);
    void removePlayer(net::Connection const* connection);
    [[nodiscard]] std::vector<std::shared_ptr<net::Connection>> playersExcept(
        net::Connection const* connection) const;

private:
    void loadBlockItemMappings();

    struct BlockPosHash {
        size_t operator()(net::BlockPos const& position) const noexcept;
    };

    std::unordered_map<net::BlockPos, int32_t, BlockPosHash> blockOverrides_;
    std::unordered_map<int32_t, int32_t> blockItemStates_;
    std::vector<std::weak_ptr<net::Connection>> players_;
    bool dirty_ = false;
    std::unordered_set<int32_t> validBlockStates_;
    uint8_t globalBlockStateBits_ = 9;
};

} // namespace mcserver::server
