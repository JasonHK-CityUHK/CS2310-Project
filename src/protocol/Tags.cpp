#include "mcserver/protocol/Tags.hpp"

#include <algorithm>
#include <filesystem>
#include <map>
#include <set>

#ifndef MCSERVER_TAG_DATA_DIR
#error "MCSERVER_TAG_DATA_DIR must be defined by the build (see src/CMakeLists.txt)"
#endif

namespace mcserver::protocol {

std::vector<TaggedRegistry> buildMinimalTags() {
    // Registry codecs only require referenced tags to be bound. Keep entries
    // empty until the server has real numeric IDs for the corresponding
    // registries; declaring the complete tag set is enough for configuration.
    std::map<std::string, std::vector<TagDefinition>> tagsByRegistry;
    std::filesystem::path root = MCSERVER_TAG_DATA_DIR;
    if (!std::filesystem::exists(root)) { return {}; }

    // Update Tags may refer to built-in registries without a Registry Data
    // packet, but a tag for an optional synchronized registry is only valid if
    // that registry was sent as well.
    std::set<std::string> sentRegistries{
        "minecraft:attribute", "minecraft:block", "minecraft:block_entity_type", "minecraft:consume_effect_type",
        "minecraft:custom_stat", "minecraft:data_component_type", "minecraft:entity_type", "minecraft:fluid",
        "minecraft:game_event", "minecraft:item", "minecraft:menu", "minecraft:mob_effect",
        "minecraft:particle_type", "minecraft:potion", "minecraft:recipe_book_category", "minecraft:recipe_display",
        "minecraft:slot_display", "minecraft:sound_event", "minecraft:stat_type", "minecraft:villager_type",
        "minecraft:block_transformer", "minecraft:decorated_pot_pattern", "minecraft:enchantment_provider",
    };
    std::filesystem::path registryRoot = MCSERVER_REGISTRY_DATA_DIR;
    if (std::filesystem::exists(registryRoot)) {
        for (auto const& entry : std::filesystem::directory_iterator(registryRoot)) {
            if (!entry.is_directory()) { continue; }
            std::string registryPath = entry.path().filename().string();
            if (registryPath == "worldgen") {
                for (auto const& nested : std::filesystem::directory_iterator(entry.path())) {
                    if (nested.is_directory()) { sentRegistries.insert("minecraft:worldgen/" + nested.path().filename().string()); }
                }
            } else {
                sentRegistries.insert("minecraft:" + registryPath);
            }
        }
    }

    for (auto const& file : std::filesystem::recursive_directory_iterator(root)) {
        if (!file.is_regular_file() || file.path().extension() != ".json") { continue; }
        auto relative = std::filesystem::relative(file.path(), root);
        std::vector<std::string> components;
        for (auto const& component : relative) { components.push_back(component.string()); }
        if (components.size() < 2) { continue; }

        std::string registryPath = components.front();
        size_t tagStart = 1;
        if (registryPath == "worldgen" && components.size() >= 3) {
            registryPath += "/" + components[1];
            tagStart = 2;
        }

        std::string tagPath;
        for (size_t index = tagStart; index < components.size(); ++index) {
            if (!tagPath.empty()) { tagPath += "/"; }
            tagPath += components[index];
        }
        if (tagPath.size() < 5 || tagPath.substr(tagPath.size() - 5) != ".json") { continue; }
        tagPath.resize(tagPath.size() - 5);

        std::string registryId = "minecraft:" + registryPath;
        if (!sentRegistries.contains(registryId)) { continue; }
        tagsByRegistry[std::move(registryId)].push_back({"minecraft:" + tagPath, {}});
    }

    std::vector<TaggedRegistry> result;
    for (auto& [registryId, tags] : tagsByRegistry) {
        std::sort(tags.begin(), tags.end(), [](TagDefinition const& left, TagDefinition const& right) {
            return left.name < right.name;
        });
        result.push_back({std::move(registryId), std::move(tags)});
    }
    return result;
}

} // namespace mcserver::protocol
