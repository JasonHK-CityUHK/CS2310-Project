#include "mcserver/protocol/Registries.hpp"
#include "mcserver/protocol/DataPaths.hpp"
#include "mcserver/protocol/JsonToNbt.hpp"
#include "mcserver/util/Logger.hpp"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <array>

namespace mcserver::protocol {

namespace {

std::string readFile(std::filesystem::path const& path) {
    std::ifstream file(path, std::ios::binary);
    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}

// Loads one registry's worth of entries from a flat directory of `<entry>.json` files.
Registry loadRegistryDir(std::string registryId, std::filesystem::path const& dir) {
    Registry registry;
    registry.id = std::move(registryId);

    std::vector<std::filesystem::path> jsonFiles;
    for (auto const& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") { jsonFiles.push_back(entry.path()); }
    }
    // Sort for reproducible entry ordering (and thus reproducible numeric IDs) across runs.
    std::sort(jsonFiles.begin(), jsonFiles.end());

    for (auto const& path : jsonFiles) {
        std::string entryId = "minecraft:" + path.stem().string();
        std::string json = readFile(path);
        try {
            nlohmann::json parsed = nlohmann::json::parse(json);
            registry.entries.push_back({std::move(entryId), jsonValueToNbt(parsed)});
        } catch (std::exception const& e) {
            util::log(util::LogLevel::Warning,
                      "failed to parse " + path.string() + " as JSON (" + e.what() + "); skipping entry " +
                          entryId + " in registry " + registry.id);
        }
    }
    return registry;
}

} // namespace

std::vector<Registry> loadRegistriesFromDirectory(std::filesystem::path const& root) {
    std::vector<Registry> registries;
    if (!std::filesystem::exists(root)) {
        util::log(util::LogLevel::Warning, "registry data directory does not exist: " + root.string());
        return registries;
    }

    for (auto const& entry : std::filesystem::directory_iterator(root)) {
        if (!entry.is_directory()) { continue; }
        std::string dirName = entry.path().filename().string();

        if (dirName == "worldgen") {
            auto biomeDir = entry.path() / "biome";
            if (std::filesystem::exists(biomeDir)) {
                registries.push_back(loadRegistryDir("minecraft:worldgen/biome", biomeDir));
            }
            continue;
        }

        registries.push_back(loadRegistryDir("minecraft:" + dirName, entry.path()));
    }

    // New 26.3 protocol registries live directly under data/minecraft rather
    // than under the synchronized-registry directory used above.
    auto vanillaDataRoot = vanillaDataPath();
    constexpr std::array supplementalRegistries{"block_transformer", "decorated_pot_pattern", "enchantment_provider"};
    for (auto registryName : supplementalRegistries) {
        auto directory = vanillaDataRoot / registryName;
        if (std::filesystem::exists(directory)) {
            registries.push_back(loadRegistryDir("minecraft:" + std::string(registryName), directory));
        }
    }

    // Deterministic registry order too, purely for reproducible logs/diffing.
    std::sort(registries.begin(), registries.end(), [](Registry const& a, Registry const& b) { return a.id < b.id; });
    return registries;
}

std::vector<Registry> buildMinimalRegistries() { return loadRegistriesFromDirectory(registryDataPath()); }

} // namespace mcserver::protocol

