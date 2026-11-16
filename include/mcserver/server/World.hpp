#pragma once

#include "mcserver/net/ByteBuffer.hpp"
#include "mcserver/server/AnvilWorld.hpp"

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
    void loadAnvil(std::filesystem::path const& directory);
    [[nodiscard]] AnvilWorld::Spawn spawn() const { return imported_ ? imported_->spawn() : AnvilWorld::Spawn{0.5,1.0,0.5,0,0}; }
    [[nodiscard]] bool imported() const { return imported_ != nullptr; }
    [[nodiscard]] std::string identity() const { return imported_ ? imported_->identity() : "flat-stone-v1"; }
    [[nodiscard]] std::string worldName() const { return imported_ ? imported_->name() : "flat world"; }
    [[nodiscard]] int32_t biomeAt(int32_t x, int32_t y, int32_t z) const;
    [[nodiscard]] bool isAirState(int32_t state) const { return airStates_.contains(state); }
    [[nodiscard]] bool isFluidState(int32_t state) const { return fluidStates_.contains(state); }
    [[nodiscard]] uint8_t globalBiomeBits() const { return globalBiomeBits_; }

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
    int32_t baseStateAt(net::BlockPos const& position) const;
    bool editable(net::BlockPos const& position) const;
    std::shared_ptr<AnvilWorld> imported_;
    std::unordered_map<std::string, int32_t> blockStateIds_, defaultStates_, biomeIds_;
    std::unordered_set<int32_t> airStates_, fluidStates_;
    uint8_t globalBiomeBits_ = 6;

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
