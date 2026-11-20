#include "mcserver/server/SectionData.hpp"

#include <catch2/catch_test_macros.hpp>

namespace {

int32_t resolve(nbt::CompoundTagVariant const& entry) {
    return std::stoi(static_cast<std::string const&>(entry));
}

} // namespace

TEST_CASE("Section block palettes decode single and padded five-bit states", "[section-data]") {
    nbt::CompoundTag single{{"palette", nbt::ListTag({"7"})}};
    auto uniform = mcserver::server::decodeBlockStates(single, resolve);
    REQUIRE(uniform.front() == 7);
    REQUIRE(uniform.back() == 7);
    single["data"] = nbt::LongArrayTag(std::vector<int64_t>(256, 0));
    REQUIRE(mcserver::server::decodeBlockStates(single, resolve) == uniform);
    single["data"] = nbt::LongArrayTag(std::vector<int64_t>(256, 1));
    REQUIRE_THROWS(mcserver::server::decodeBlockStates(single, resolve));
    std::vector<nbt::CompoundTagVariant> palette;
    for (int index = 0; index < 17; ++index) { palette.emplace_back(std::to_string(index)); }
    std::vector<int64_t> words((4096 + 11) / 12, 0);
    words[0] = static_cast<int64_t>(uint64_t{16} << 55);
    words[1] = 9;
    nbt::CompoundTag states{{"palette", nbt::ListTag(std::move(palette))}, {"data", nbt::LongArrayTag(words)}};
    auto decoded = mcserver::server::decodeBlockStates(states, resolve);
    REQUIRE(decoded[11] == 16);
    REQUIRE(decoded[12] == 9);
    REQUIRE(decoded[13] == 0);
}

TEST_CASE("Section block palettes reject malformed packed data", "[section-data]") {
    nbt::CompoundTag states{{"palette", nbt::ListTag({"0", "1"})}};
    REQUIRE_THROWS(mcserver::server::decodeBlockStates(states, resolve));
    states["data"] = nbt::LongArrayTag(std::vector<int64_t>(256, 2));
    REQUIRE_THROWS(mcserver::server::decodeBlockStates(states, resolve));
    states["data"] = nbt::LongArrayTag(std::vector<int64_t>(1, 0));
    REQUIRE_THROWS(mcserver::server::decodeBlockStates(states, resolve));
}

TEST_CASE("Block state registry resolves 26.3 palette variants", "[section-data]") {
    mcserver::server::BlockStateRegistry registry;
    REQUIRE(registry.resolve(nbt::CompoundTagVariant("minecraft:stone")) == 1);
    REQUIRE(registry.resolve(nbt::CompoundTag{{"id", "minecraft:stone"}}) == 1);
    REQUIRE(registry.resolve(nbt::CompoundTag{{"", "minecraft:stone"}}) == 1);
    REQUIRE(registry.resolve(registry.paletteEntry(1)) == 1);
    REQUIRE_THROWS(registry.resolve(nbt::CompoundTagVariant("minecraft:not_a_block")));
    REQUIRE(registry.isAir(registry.resolve(nbt::CompoundTagVariant("minecraft:cave_air"))));
    REQUIRE(registry.hasFluid(registry.resolve(nbt::CompoundTagVariant("minecraft:water"))));
    REQUIRE_FALSE(registry.hasFluid(1));
}

TEST_CASE("Encoded block sections round trip runtime states", "[section-data]") {
    mcserver::server::BlockStateRegistry registry;
    std::array<int32_t, 4096> states{};
    for (size_t index = 0; index < states.size(); ++index) { states[index] = static_cast<int32_t>(index % 17); }
    auto encoded = mcserver::server::encodeBlockStates(states, registry);
    auto restored = mcserver::server::decodeBlockStates(encoded,
        [&registry](auto const& entry) { return registry.resolve(entry); });
    REQUIRE(restored == states);
    states.fill(1);
    encoded = mcserver::server::encodeBlockStates(states, registry);
    REQUIRE_FALSE(encoded.contains("data"));
    REQUIRE(mcserver::server::decodeBlockStates(encoded,
        [&registry](auto const& entry) { return registry.resolve(entry); }) == states);
}

TEST_CASE("Chunk section decoding handles negative and missing sections", "[section-data]") {
    nbt::CompoundTag stone{{"palette", nbt::ListTag({"1"})}};
    nbt::CompoundTag section{{"Y", static_cast<int8_t>(-4)}, {"block_states", stone}};
    nbt::CompoundTag boundary{{"Y", static_cast<int8_t>(-5)}};
    nbt::CompoundTag chunk{{"sections", nbt::ListTag({section, boundary})}};
    auto decoded = mcserver::server::decodeChunkSections(chunk, resolve);
    REQUIRE(decoded[0][0] == 1);
    REQUIRE(decoded[1][0] == 0);
    REQUIRE(decoded[23][4095] == 0);
    chunk["sections"] = nbt::ListTag({section, section});
    REQUIRE_THROWS(mcserver::server::decodeChunkSections(chunk, resolve));
    boundary["block_states"] = stone;
    chunk["sections"] = nbt::ListTag({boundary});
    REQUIRE_THROWS(mcserver::server::decodeChunkSections(chunk, resolve));
}

TEST_CASE("Chunk biome palettes decode padded entries", "[section-data]") {
    std::unordered_map<std::string, int32_t> biomes{{"minecraft:plains", 41}, {"minecraft:desert", 5},
                                                    {"minecraft:forest", 6}};
    nbt::CompoundTag biomeData{{"palette", nbt::ListTag({"minecraft:plains", "minecraft:desert", "minecraft:forest"})},
                               {"data", nbt::LongArrayTag({static_cast<int64_t>(2 | (uint64_t{1} << 62)), 2})}};
    nbt::CompoundTag section{{"Y", static_cast<int8_t>(0)}, {"biomes", biomeData}};
    nbt::CompoundTag chunk{{"sections", nbt::ListTag({section})}};
    auto decoded = mcserver::server::decodeChunkBiomes(chunk, biomes);
    REQUIRE(decoded[4][0] == 6);
    REQUIRE(decoded[4][31] == 5);
    REQUIRE(decoded[4][32] == 6);
    REQUIRE(decoded[0][0] == 41);
    section["biomes"].as<nbt::CompoundTag>()["data"] = nbt::LongArrayTag({3, 0});
    chunk["sections"] = nbt::ListTag({section});
    REQUIRE_THROWS(mcserver::server::decodeChunkBiomes(chunk, biomes));
}
