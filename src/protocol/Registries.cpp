#include "mcserver/protocol/Registries.hpp"

namespace mcserver::protocol {

namespace {

nbt::CompoundTag buildOverworldDimensionType() {
    // Mirrors vanilla's data/minecraft/dimension_type/overworld.json.
    // monster_spawn_light_level must be a full IntProvider object; a bare int is rejected by the codec.
    nbt::CompoundTag monsterSpawnLightLevel{
        {"type", std::string("minecraft:uniform")},
        {"min_inclusive", 0},
        {"max_inclusive", 7},
    };
    return nbt::CompoundTag{
        {"piglin_safe", false},
        {"has_raids", true},
        {"monster_spawn_light_level", std::move(monsterSpawnLightLevel)},
        {"monster_spawn_block_light_limit", 0},
        {"natural", true},
        {"ambient_light", 0.0f},
        {"infiniburn", std::string("#minecraft:infiniburn_overworld")},
        {"respawn_anchor_works", false},
        {"has_skylight", true},
        {"bed_works", true},
        {"effects", std::string("minecraft:overworld")},
        {"min_y", -64},
        {"height", 384},
        {"logical_height", 384},
        {"coordinate_scale", 1.0},
        {"ultrawarm", false},
        {"has_ceiling", false},
    };
}

nbt::CompoundTag buildPlainsBiome() {
    // Mirrors vanilla's data/minecraft/worldgen/biome/plains.json (minus optional fields).
    nbt::CompoundTag moodSound{
        {"sound", std::string("minecraft:ambient.cave")},
        {"tick_delay", 6000},
        {"block_search_extent", 8},
        {"offset", 2.0},
    };
    nbt::CompoundTag effects{
        {"sky_color", 7842047},
        {"fog_color", 12638463},
        {"water_color", 4159204},
        {"water_fog_color", 329011},
        {"mood_sound", std::move(moodSound)},
    };
    return nbt::CompoundTag{
        {"has_precipitation", true},
        {"temperature", 0.8f},
        {"downfall", 0.4f},
        {"effects", std::move(effects)},
    };
}

} // namespace

std::vector<Registry> buildMinimalRegistries() {
    std::vector<Registry> registries;

    Registry dimensionType;
    dimensionType.id = "minecraft:dimension_type";
    dimensionType.entries.push_back({"minecraft:overworld", buildOverworldDimensionType()});
    registries.push_back(std::move(dimensionType));

    Registry biome;
    biome.id = "minecraft:worldgen/biome";
    biome.entries.push_back({"minecraft:plains", buildPlainsBiome()});
    registries.push_back(std::move(biome));

    return registries;
}

} // namespace mcserver::protocol
