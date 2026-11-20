#include "mcserver/server/SectionData.hpp"
#include "mcserver/protocol/DataPaths.hpp"

#include <algorithm>
#include <bit>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <vector>

#include <nlohmann/json.hpp>

namespace mcserver::server {
namespace {

std::string stateKey(std::string const& name, nlohmann::json const& properties) {
    return nlohmann::json::array({name, properties}).dump();
}

} // namespace

BlockStateRegistry::BlockStateRegistry() {
    std::ifstream input(protocol::vanillaReportsPath() / "blocks.json");
    if (!input) { throw std::runtime_error("cannot open Minecraft block report"); }
    nlohmann::json blocks;
    input >> blocks;
    for (auto const& [name, block] : blocks.items()) {
        for (auto const& state : block.at("states")) {
            int32_t id = state.at("id").get<int32_t>();
            auto properties = state.value("properties", nlohmann::json::object());
            if (name == "minecraft:air" || name == "minecraft:cave_air" || name == "minecraft:void_air") {
                airStates_.insert(id);
            }
            if (name == "minecraft:water" || name == "minecraft:lava" || name == "minecraft:bubble_column" ||
                name == "minecraft:kelp" || name == "minecraft:kelp_plant" || name == "minecraft:seagrass" ||
                name == "minecraft:tall_seagrass" || properties.value("waterlogged", std::string{}) == "true") {
                fluidStates_.insert(id);
            }
            states_.emplace(stateKey(name, properties), id);
            nbt::CompoundTag entry{{"id", name}};
            if (!properties.empty()) {
                nbt::CompoundTag tagProperties;
                for (auto const& [key, value] : properties.items()) { tagProperties[key] = value.get<std::string>(); }
                entry["properties"] = std::move(tagProperties);
            }
            entries_.emplace(id, std::move(entry));
            if (state.value("default", false)) { states_.emplace(stateKey(name, nlohmann::json::object()), id); }
        }
    }
}

int32_t BlockStateRegistry::resolve(nbt::CompoundTagVariant const& entry) const {
    std::string name;
    nlohmann::json properties = nlohmann::json::object();
    if (entry->getType() == nbt::Tag::Type::String) {
        name = static_cast<std::string const&>(entry);
    } else if (entry->getType() == nbt::Tag::Type::Compound) {
        auto const& compound = entry.as<nbt::CompoundTag>();
        if (compound.contains("id", nbt::Tag::Type::String)) { name = static_cast<std::string const&>(compound.at("id")); }
        else if (compound.contains("", nbt::Tag::Type::String)) { name = static_cast<std::string const&>(compound.at("")); }
        else { throw std::runtime_error("invalid block palette entry"); }
        if (compound.contains("properties")) {
            if (!compound.contains("properties", nbt::Tag::Type::Compound)) { throw std::runtime_error("invalid block properties"); }
            for (auto const& [key, value] : compound.at("properties").as<nbt::CompoundTag>().items()) {
                if (value->getType() != nbt::Tag::Type::String) { throw std::runtime_error("invalid block property value"); }
                properties[key] = static_cast<std::string const&>(value);
            }
        }
    } else { throw std::runtime_error("invalid block palette entry type"); }
    auto state = states_.find(stateKey(name, properties));
    if (state == states_.end()) { throw std::runtime_error("unknown block state: " + name); }
    return state->second;
}

nbt::CompoundTag BlockStateRegistry::paletteEntry(int32_t state) const {
    auto entry = entries_.find(state);
    if (entry == entries_.end()) { throw std::runtime_error("unknown block state ID"); }
    return entry->second;
}

std::array<int32_t, 4096> decodeBlockStates(nbt::CompoundTag const& blockStates,
                                             BlockStateResolver const& resolve) {
    if (!blockStates.contains("palette", nbt::Tag::Type::List)) {
        throw std::runtime_error("missing block state palette");
    }
    auto const& paletteTag = blockStates.at("palette").as<nbt::ListTag>();
    if (paletteTag.empty() || paletteTag.size() > 4096 ||
        (paletteTag.getElementType() != nbt::Tag::Type::String &&
         paletteTag.getElementType() != nbt::Tag::Type::Compound)) {
        throw std::runtime_error("invalid block state palette");
    }
    std::vector<int32_t> palette;
    palette.reserve(paletteTag.size());
    for (auto const& entry : paletteTag) { palette.push_back(resolve(entry)); }
    std::array<int32_t, 4096> result{};
    if (palette.size() == 1) {
        if (blockStates.contains("data")) {
            if (!blockStates.contains("data", nbt::Tag::Type::LongArray)) {
                throw std::runtime_error("invalid single-state block data");
            }
            auto const& words = blockStates.at("data").as<nbt::LongArrayTag>().storage();
            if (words.size() != 256 || std::any_of(words.begin(), words.end(), [](int64_t word) { return word != 0; })) {
                throw std::runtime_error("invalid single-state block data");
            }
        }
        result.fill(palette.front());
        return result;
    }
    if (!blockStates.contains("data", nbt::Tag::Type::LongArray)) {
        throw std::runtime_error("missing packed block states");
    }
    auto const& words = blockStates.at("data").as<nbt::LongArrayTag>().storage();
    unsigned bits = std::max<unsigned>(4, std::bit_width(palette.size() - 1));
    size_t entriesPerWord = 64 / bits;
    if (words.size() != (result.size() + entriesPerWord - 1) / entriesPerWord) {
        throw std::runtime_error("invalid packed block state length");
    }
    uint64_t mask = (uint64_t{1} << bits) - 1;
    for (size_t index = 0; index < result.size(); ++index) {
        uint64_t word = static_cast<uint64_t>(words[index / entriesPerWord]);
        size_t paletteIndex = (word >> ((index % entriesPerWord) * bits)) & mask;
        if (paletteIndex >= palette.size()) { throw std::runtime_error("invalid block state palette index"); }
        result[index] = palette[paletteIndex];
    }
    return result;
}

nbt::CompoundTag encodeBlockStates(std::array<int32_t, 4096> const& states,
                                   BlockStateRegistry const& registry) {
    std::unordered_map<int32_t, uint32_t> indices;
    std::vector<nbt::CompoundTagVariant> palette;
    std::array<uint32_t, 4096> entries{};
    for (size_t index = 0; index < states.size(); ++index) {
        auto [position, inserted] = indices.emplace(states[index], static_cast<uint32_t>(palette.size()));
        if (inserted) { palette.emplace_back(registry.paletteEntry(states[index])); }
        entries[index] = position->second;
    }
    nbt::CompoundTag result{{"palette", nbt::ListTag(std::move(palette))}};
    if (indices.size() == 1) { return result; }
    unsigned bits = std::max<unsigned>(4, std::bit_width(indices.size() - 1));
    size_t entriesPerWord = 64 / bits;
    std::vector<int64_t> words((entries.size() + entriesPerWord - 1) / entriesPerWord, 0);
    for (size_t index = 0; index < entries.size(); ++index) {
        uint64_t word = static_cast<uint64_t>(words[index / entriesPerWord]);
        word |= static_cast<uint64_t>(entries[index]) << ((index % entriesPerWord) * bits);
        words[index / entriesPerWord] = static_cast<int64_t>(word);
    }
    result["data"] = nbt::LongArrayTag(words);
    return result;
}

ChunkSections decodeChunkSections(nbt::CompoundTag const& chunk, BlockStateResolver const& resolve) {
    if (!chunk.contains("sections", nbt::Tag::Type::List)) { throw std::runtime_error("missing chunk sections"); }
    auto const& sections = chunk.at("sections").as<nbt::ListTag>();
    if (!sections.empty() && sections.getElementType() != nbt::Tag::Type::Compound) {
        throw std::runtime_error("invalid chunk section list");
    }
    ChunkSections result{};
    std::array<bool, 26> seen{};
    for (auto const& sectionTag : sections) {
        auto const& section = sectionTag.as<nbt::CompoundTag>();
        if (!section.contains("Y", nbt::Tag::Type::Byte)) { throw std::runtime_error("missing section Y"); }
        int sectionY = static_cast<int8_t>(section.at("Y").as<nbt::ByteTag>().storage());
        if (sectionY < -5 || sectionY > 20 || seen[static_cast<size_t>(sectionY + 5)]) {
            throw std::runtime_error("invalid or duplicate section Y");
        }
        seen[static_cast<size_t>(sectionY + 5)] = true;
        if (!section.contains("block_states")) { continue; }
        if (sectionY < -4 || sectionY > 19 || !section.contains("block_states", nbt::Tag::Type::Compound)) {
            throw std::runtime_error("invalid section block states");
        }
        result[static_cast<size_t>(sectionY + 4)] =
            decodeBlockStates(section.at("block_states").as<nbt::CompoundTag>(), resolve);
    }
    return result;
}

BiomeSections decodeChunkBiomes(nbt::CompoundTag const& chunk,
                                 std::unordered_map<std::string, int32_t> const& biomes) {
    auto plains = biomes.find("minecraft:plains");
    if (plains == biomes.end()) { throw std::runtime_error("plains biome not in registry"); }
    BiomeSections result;
    for (auto& section : result) { section.fill(plains->second); }
    auto const& sections = chunk.at("sections").as<nbt::ListTag>();
    for (auto const& sectionTag : sections) {
        auto const& section = sectionTag.as<nbt::CompoundTag>();
        int sectionY = static_cast<int8_t>(section.at("Y").as<nbt::ByteTag>().storage());
        if (sectionY < -4 || sectionY > 19 || !section.contains("biomes")) { continue; }
        if (!section.contains("biomes", nbt::Tag::Type::Compound)) { throw std::runtime_error("invalid biome container"); }
        auto const& container = section.at("biomes").as<nbt::CompoundTag>();
        if (!container.contains("palette", nbt::Tag::Type::List)) { throw std::runtime_error("missing biome palette"); }
        auto const& paletteTag = container.at("palette").as<nbt::ListTag>();
        if (paletteTag.empty() || paletteTag.size() > 64 || paletteTag.getElementType() != nbt::Tag::Type::String) {
            throw std::runtime_error("invalid biome palette");
        }
        std::vector<int32_t> palette;
        for (auto const& entry : paletteTag) {
            auto found = biomes.find(static_cast<std::string const&>(entry));
            if (found == biomes.end()) { throw std::runtime_error("unknown biome in chunk"); }
            palette.push_back(found->second);
        }
        auto& decoded = result[static_cast<size_t>(sectionY + 4)];
        if (palette.size() == 1) { decoded.fill(palette.front()); continue; }
        if (!container.contains("data", nbt::Tag::Type::LongArray)) { throw std::runtime_error("missing biome data"); }
        auto const& words = container.at("data").as<nbt::LongArrayTag>().storage();
        unsigned bits = std::bit_width(palette.size() - 1);
        size_t perWord = 64 / bits;
        if (words.size() != (64 + perWord - 1) / perWord) { throw std::runtime_error("invalid biome data length"); }
        uint64_t mask = (uint64_t{1} << bits) - 1;
        for (size_t index = 0; index < decoded.size(); ++index) {
            size_t paletteIndex = (static_cast<uint64_t>(words[index / perWord]) >> ((index % perWord) * bits)) & mask;
            if (paletteIndex >= palette.size()) { throw std::runtime_error("invalid biome palette index"); }
            decoded[index] = palette[paletteIndex];
        }
    }
    return result;
}

} // namespace mcserver::server
