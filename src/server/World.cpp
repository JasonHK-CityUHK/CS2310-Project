#include "mcserver/server/World.hpp"

#include "mcserver/net/Connection.hpp"

#include <algorithm>
#include <bit>
#include <filesystem>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <tuple>

#include <nlohmann/json.hpp>

namespace mcserver::server {

World::World() { loadBlockItemMappings(); }

int32_t World::blockStateAt(net::BlockPos const& position) const {
    if (auto block = blockOverrides_.find(position); block != blockOverrides_.end()) {
        return block->second;
    }
    return position.y == 0 ? 1 : 0;
}

bool World::contains(net::BlockPos const& position) {
    return position.x >= -33554432 && position.x <= 33554431 &&
           position.z >= -33554432 && position.z <= 33554431 && position.y >= -64 && position.y < 320;
}

void World::setBlockToAir(net::BlockPos const& position) {
    if (!contains(position) || blockStateAt(position) == 0) { return; }
    if (position.y == 0) { blockOverrides_[position] = 0; }
    else { blockOverrides_.erase(position); }
    dirty_ = true;
}

std::vector<World::BlockChange> World::blockChanges() const {
    std::vector<BlockChange> result;
    result.reserve(blockOverrides_.size());
    for (auto const& [position, state] : blockOverrides_) { result.push_back({position, state}); }
    std::sort(result.begin(), result.end(), [](auto const& left, auto const& right) {
        return std::tie(left.position.x, left.position.y, left.position.z) <
               std::tie(right.position.x, right.position.y, right.position.z);
    });
    return result;
}

void World::restoreChanges(std::vector<BlockChange> const& changes) {
    decltype(blockOverrides_) restored;
    for (auto const& change : changes) {
        if (!contains(change.position) || !validBlockState(change.state) ||
            !restored.emplace(change.position, change.state).second) {
            throw std::runtime_error("invalid or duplicate world block override");
        }
    }
    blockOverrides_ = std::move(restored);
    dirty_ = false;
}

bool World::tryPlaceBlock(net::BlockPos const& position, int32_t blockState) {
    if (!contains(position) || !validBlockState(blockState) || blockState == 0 || blockStateAt(position) != 0) { return false; }
    if (position.y == 0 && blockState == 1) { blockOverrides_.erase(position); }
    else { blockOverrides_[position] = blockState; }
    dirty_ = true;
    return true;
}

std::optional<int32_t> World::blockStateForItem(int32_t itemId) const {
    auto block = blockItemStates_.find(itemId);
    if (block == blockItemStates_.end()) { return std::nullopt; }
    return block->second;
}

void World::addPlayer(std::shared_ptr<net::Connection> const& connection) {
    std::erase_if(players_, [&connection](auto const& player) {
        auto current = player.lock();
        return !current || current == connection;
    });
    players_.push_back(connection);
}

void World::removePlayer(net::Connection const* connection) {
    std::erase_if(players_, [connection](auto const& player) {
        auto current = player.lock();
        return !current || current.get() == connection;
    });
}

std::vector<std::shared_ptr<net::Connection>> World::playersExcept(
    net::Connection const* connection) const {
    std::vector<std::shared_ptr<net::Connection>> players;
    for (auto const& player : players_) {
        if (auto current = player.lock(); current && current.get() != connection) {
            players.push_back(std::move(current));
        }
    }
    return players;
}

size_t World::BlockPosHash::operator()(net::BlockPos const& position) const noexcept {
    size_t hash = std::hash<int32_t>{}(position.x);
    hash ^= std::hash<int32_t>{}(position.y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    hash ^= std::hash<int32_t>{}(position.z) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    return hash;
}

void World::loadBlockItemMappings() {
    std::ifstream registryFile(std::filesystem::path(MCSERVER_VANILLA_REPORTS_DIR) / "registries.json");
    if (!registryFile) {
        throw std::runtime_error("failed to open Minecraft registry report");
    }
    std::ifstream blocksFile(std::filesystem::path(MCSERVER_VANILLA_REPORTS_DIR) / "blocks.json");
    if (!blocksFile) {
        throw std::runtime_error("failed to open Minecraft block report");
    }

    nlohmann::json registries;
    nlohmann::json blocks;
    registryFile >> registries;
    blocksFile >> blocks;

    for (auto const& [blockName, blockData] : blocks.items()) {
        (void)blockName;
        for (auto const& state : blockData.at("states")) {
            validBlockStates_.insert(state.at("id").get<int32_t>());
            globalBlockStateBits_ =
                std::max(globalBlockStateBits_,
                         static_cast<uint8_t>(std::bit_width(state.at("id").get<uint32_t>())));
        }
    }

    auto const& items = registries.at("minecraft:item").at("entries");
    for (auto const& [itemName, itemData] : items.items()) {
        auto block = blocks.find(itemName);
        if (block == blocks.end()) { continue; }

        for (auto const& state : block->at("states")) {
            if (state.value("default", false)) {
                blockItemStates_[itemData.at("protocol_id").get<int32_t>()] =
                    state.at("id").get<int32_t>();
            }
        }
    }
}

} // namespace mcserver::server
