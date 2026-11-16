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
#include "mcserver/protocol/DataPaths.hpp"

namespace mcserver::server {

namespace {
std::string stateKey(std::string const& name, AnvilWorld::Properties const& properties) {
    std::string key = name;
    for (auto const& [property, value] : properties) { key += "|" + property + "=" + value; }
    return key;
}
}

World::World() { loadBlockItemMappings(); }

void World::loadAnvil(std::filesystem::path const& directory) {
    auto restored = std::make_shared<AnvilWorld>(directory,
        [this](std::string const& name, AnvilWorld::Properties const& properties) {
            auto const& table = properties.empty() ? defaultStates_ : blockStateIds_;
            auto found = table.find(properties.empty() ? name : stateKey(name, properties));
            if (found == table.end()) { throw std::runtime_error("unknown block state in world: " + stateKey(name, properties)); }
            return found->second;
        }, [this](std::string const& name) {
            auto found = biomeIds_.find(name);
            if (found == biomeIds_.end()) { throw std::runtime_error("unknown biome in world: " + name); }
            return found->second;
        });
    imported_ = std::move(restored);
    blockOverrides_.clear();
    dirty_ = false;
}

int32_t World::baseStateAt(net::BlockPos const& position) const {
    return imported_ ? imported_->blockStateAt(position) : (position.y == 0 ? 1 : 0);
}
bool World::editable(net::BlockPos const& position) const {
    return contains(position) && (!imported_ || imported_->contains(position));
}
int32_t World::biomeAt(int32_t x, int32_t y, int32_t z) const {
    return imported_ ? imported_->biomeAt(x,y,z) : 41;
}

int32_t World::blockStateAt(net::BlockPos const& position) const {
    if (auto block = blockOverrides_.find(position); block != blockOverrides_.end()) {
        return block->second;
    }
    return baseStateAt(position);
}

bool World::contains(net::BlockPos const& position) {
    return position.x >= -33554432 && position.x <= 33554431 &&
           position.z >= -33554432 && position.z <= 33554431 && position.y >= -64 && position.y < 320;
}

void World::setBlockToAir(net::BlockPos const& position) {
    if (!editable(position) || isAirState(blockStateAt(position))) { return; }
    if (baseStateAt(position) != 0) { blockOverrides_[position] = 0; }
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
        if (!editable(change.position) || !validBlockState(change.state) ||
            !restored.emplace(change.position, change.state).second) {
            throw std::runtime_error("invalid or duplicate world block override");
        }
    }
    blockOverrides_ = std::move(restored);
    dirty_ = false;
}

bool World::tryPlaceBlock(net::BlockPos const& position, int32_t blockState) {
    if (!editable(position) || !validBlockState(blockState) || isAirState(blockState) || !isAirState(blockStateAt(position))) { return false; }
    if (baseStateAt(position) == blockState) { blockOverrides_.erase(position); }
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

        for (auto const& state : blockData.at("states")) {
            auto stateId = state.at("id").get<int32_t>();
            validBlockStates_.insert(stateId);
            AnvilWorld::Properties properties;
            if (state.contains("properties")) {
                for (auto const& [key, value] : state.at("properties").items()) { properties[key] = value.get<std::string>(); }
            }
            blockStateIds_[stateKey(blockName, properties)] = stateId;
            if (state.value("default", false)) { defaultStates_[blockName] = stateId; }
            if (blockName == "minecraft:air" || blockName == "minecraft:cave_air" || blockName == "minecraft:void_air") { airStates_.insert(stateId); }
            if (blockName == "minecraft:water" || blockName == "minecraft:lava" || blockName == "minecraft:bubble_column" ||
                (properties.contains("waterlogged") && properties.at("waterlogged") == "true")) { fluidStates_.insert(stateId); }
            globalBlockStateBits_ =
                std::max(globalBlockStateBits_,
                         static_cast<uint8_t>(std::bit_width(state.at("id").get<uint32_t>())));
        }
    }

    std::vector<std::filesystem::path> biomes;
    for (auto const& entry : std::filesystem::directory_iterator(protocol::registryDataPath() / "worldgen/biome")) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") { biomes.push_back(entry.path()); }
    }
    std::sort(biomes.begin(), biomes.end());
    for (size_t index = 0; index < biomes.size(); ++index) { biomeIds_["minecraft:" + biomes[index].stem().string()] = static_cast<int32_t>(index); }
    globalBiomeBits_ = static_cast<uint8_t>(std::bit_width(biomes.size() - 1));

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
