#include "mcserver/server/JavaWorld.hpp"

#include "mcserver/server/RegionFile.hpp"
#include "mcserver/server/World.hpp"
#include "mcserver/protocol/Registries.hpp"

#include <cmath>
#include <bit>
#include <array>
#include <fstream>
#include <stdexcept>

namespace mcserver::server {
namespace {

constexpr size_t kMaxCachedChunks = 64;

int32_t chunkCoordinate(int32_t coordinate) {
    return coordinate / 16 - (coordinate % 16 < 0 ? 1 : 0);
}

uint64_t chunkKey(int32_t chunkX, int32_t chunkZ) {
    return (static_cast<uint64_t>(static_cast<uint32_t>(chunkX)) << 32) | static_cast<uint32_t>(chunkZ);
}

bool hasPoiChunk(std::filesystem::path const& directory, int32_t chunkX, int32_t chunkZ) {
    auto regionCoordinate = [](int32_t value) { return value / 32 - (value % 32 < 0 ? 1 : 0); };
    int32_t regionX = regionCoordinate(chunkX);
    int32_t regionZ = regionCoordinate(chunkZ);
    auto path = directory / "dimensions/minecraft/overworld/poi" /
                ("r." + std::to_string(regionX) + "." + std::to_string(regionZ) + ".mca");
    if (!std::filesystem::exists(path)) { return false; }
    auto size = std::filesystem::file_size(path);
    if (size < 8192 || size % 4096 != 0) { throw std::runtime_error("invalid POI region file"); }
    std::ifstream input(path, std::ios::binary);
    if (!input) { throw std::runtime_error("cannot read POI region file"); }
    int32_t localX = chunkX - regionX * 32;
    int32_t localZ = chunkZ - regionZ * 32;
    input.seekg((localX + localZ * 32) * 4);
    std::array<unsigned char, 4> location{};
    if (!input.read(reinterpret_cast<char*>(location.data()), location.size())) { throw std::runtime_error("truncated POI region file"); }
    uint32_t offset = (static_cast<uint32_t>(location[0]) << 16) |
                      (static_cast<uint32_t>(location[1]) << 8) | location[2];
    uint32_t count = location[3];
    if (offset == 0 && count == 0) { return false; }
    if (offset < 2 || count == 0 || static_cast<uint64_t>(offset) + count > size / 4096) {
        throw std::runtime_error("invalid POI region allocation");
    }
    return true;
}

} // namespace

JavaWorld::JavaWorld(std::filesystem::path const& directory)
    : lock_(directory), directory_(lock_.directory()), level_(loadLevelData(directory_)) {
    for (auto const& registry : protocol::buildMinimalRegistries()) {
        if (registry.id != "minecraft:worldgen/biome") { continue; }
        for (size_t index = 0; index < registry.entries.size(); ++index) {
            biomeIds_.emplace(registry.entries[index].id, static_cast<int32_t>(index));
        }
        biomeBits_ = static_cast<uint8_t>(std::bit_width(registry.entries.size() - 1));
    }
    if (biomeIds_.empty()) { throw std::runtime_error("biome registry is empty"); }
    if (level_.spawnDimension != "minecraft:overworld" ||
        !World::contains({level_.spawnX, level_.spawnY, level_.spawnZ}) ||
        !std::isfinite(level_.spawnYaw) || !std::isfinite(level_.spawnPitch)) {
        throw std::runtime_error("invalid or unsupported world spawn");
    }
    if (!chunk(chunkCoordinate(level_.spawnX), chunkCoordinate(level_.spawnZ))) {
        throw std::runtime_error("world spawn chunk is missing");
    }
}

std::shared_ptr<JavaWorld::Chunk const> JavaWorld::chunk(int32_t chunkX, int32_t chunkZ) {
    if (chunkX < -2097152 || chunkX > 2097151 || chunkZ < -2097152 || chunkZ > 2097151) { return nullptr; }
    uint64_t key = chunkKey(chunkX, chunkZ);
    if (auto existing = chunks_.find(key); existing != chunks_.end()) {
        recentlyUsed_.splice(recentlyUsed_.begin(), recentlyUsed_, existing->second.position);
        return existing->second.chunk;
    }
    bool external = false;
    auto data = loadRegionChunk(directory_, chunkX, chunkZ, &external);
    if (!data) { return nullptr; }
    auto loaded = std::make_shared<Chunk>();
    loaded->sections = decodeChunkSections(*data, [this](auto const& entry) { return registry_.resolve(entry); });
    loaded->biomes = decodeChunkBiomes(*data, biomeIds_);
    loaded->data = std::move(*data);
    loaded->external = external;
    if (chunks_.size() == kMaxCachedChunks) {
        auto candidate = recentlyUsed_.end();
        while (candidate != recentlyUsed_.begin()) {
            --candidate;
            if (!dirty_.contains(*candidate)) { break; }
        }
        if (dirty_.contains(*candidate)) { throw std::runtime_error("too many unsaved chunks"); }
        chunks_.erase(*candidate);
        recentlyUsed_.erase(candidate);
    }
    recentlyUsed_.push_front(key);
    auto [position, inserted] = chunks_.emplace(key, CachedChunk{std::move(loaded), recentlyUsed_.begin()});
    if (!inserted) { throw std::runtime_error("duplicate cached chunk"); }
    return position->second.chunk;
}

std::optional<int32_t> JavaWorld::blockStateAt(net::BlockPos const& position) {
    if (!World::contains(position)) { return std::nullopt; }
    int32_t chunkX = chunkCoordinate(position.x);
    int32_t chunkZ = chunkCoordinate(position.z);
    auto loaded = chunk(chunkX, chunkZ);
    if (!loaded) { return std::nullopt; }
    size_t localX = static_cast<size_t>(position.x - chunkX * 16);
    size_t localZ = static_cast<size_t>(position.z - chunkZ * 16);
    size_t section = static_cast<size_t>((position.y + 64) / 16);
    size_t localY = static_cast<size_t>((position.y + 64) % 16);
    return loaded->sections[section][localY * 256 + localZ * 16 + localX];
}

bool JavaWorld::setBlock(net::BlockPos const& position, int32_t state) {
    if ((state != 0 && (!registry_.hasState(state) || registry_.isAir(state))) ||
        !World::contains(position) || position.y <= -64 || position.y >= 319) {
        return false;
    }
    int32_t chunkX = chunkCoordinate(position.x);
    int32_t chunkZ = chunkCoordinate(position.z);
    int32_t localX = position.x - chunkX * 16;
    int32_t localZ = position.z - chunkZ * 16;
    auto current = blockStateAt(position);
    if (!current || *current == state ||
        (state == 0 ? registry_.isAir(*current) : !registry_.isAir(*current))) {
        return false;
    }
    auto key = chunkKey(chunkX, chunkZ);
    auto found = chunks_.find(key);
    if (found == chunks_.end()) { return false; }
    auto& chunk = *found->second.chunk;
    if (chunk.external) { return false; }
    if (hasPoiChunk(directory_, chunkX, chunkZ)) { return false; }
    for (auto name : {"block_entities", "block_ticks", "fluid_ticks"}) {
        if (chunk.data.contains(name) &&
            (!chunk.data.contains(name, nbt::Tag::Type::List) || !chunk.data.at(name).as<nbt::ListTag>().empty())) {
            return false;
        }
    }
    size_t sectionIndex = static_cast<size_t>((position.y + 64) / 16);
    size_t blockIndex = static_cast<size_t>((position.y + 64) % 16) * 256 +
                        static_cast<size_t>(localZ) * 16 + static_cast<size_t>(localX);
    auto updated = chunk.sections[sectionIndex];
    updated[blockIndex] = state;
    auto encoded = encodeBlockStates(updated, registry_);
    auto& sections = chunk.data["sections"].as<nbt::ListTag>();
    for (auto& sectionTag : sections) {
        auto& section = sectionTag.as<nbt::CompoundTag>();
        int sectionY = static_cast<int8_t>(section.at("Y").as<nbt::ByteTag>().storage());
        if (sectionY == static_cast<int>(sectionIndex) - 4) {
            dirty_.insert(key);
            section["block_states"] = std::move(encoded);
            chunk.sections[sectionIndex] = updated;
            return true;
        }
    }
    return false;
}

void JavaWorld::save() {
    while (!dirty_.empty()) {
        auto iterator = dirty_.begin();
        uint64_t key = *iterator;
        int32_t chunkX = std::bit_cast<int32_t>(static_cast<uint32_t>(key >> 32));
        int32_t chunkZ = std::bit_cast<int32_t>(static_cast<uint32_t>(key));
        saveRegionChunk(lock_, directory_, chunkX, chunkZ, chunks_.at(key).chunk->data);
        dirty_.erase(iterator);
    }
}

} // namespace mcserver::server
