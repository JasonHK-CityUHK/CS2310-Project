#pragma once

#include <cstdlib>
#include <filesystem>

#ifndef MCSERVER_REGISTRY_DATA_DIR
#error "MCSERVER_REGISTRY_DATA_DIR must be defined by the build"
#endif
#ifndef MCSERVER_TAG_DATA_DIR
#error "MCSERVER_TAG_DATA_DIR must be defined by the build"
#endif
#ifndef MCSERVER_VANILLA_DATA_DIR
#error "MCSERVER_VANILLA_DATA_DIR must be defined by the build"
#endif

namespace mcserver::protocol {

inline std::filesystem::path registryDataPath() {
    if (char const* dataRoot = std::getenv("MCSERVER_DATA_DIR"); dataRoot && *dataRoot) {
        return std::filesystem::path(dataRoot) / "registries";
    }
    return MCSERVER_REGISTRY_DATA_DIR;
}

inline std::filesystem::path tagDataPath() {
    if (char const* dataRoot = std::getenv("MCSERVER_DATA_DIR"); dataRoot && *dataRoot) {
        return std::filesystem::path(dataRoot) / "data/minecraft/tags";
    }
    return MCSERVER_TAG_DATA_DIR;
}

inline std::filesystem::path vanillaDataPath() {
    if (char const* dataRoot = std::getenv("MCSERVER_DATA_DIR"); dataRoot && *dataRoot) {
        return std::filesystem::path(dataRoot) / "data/minecraft";
    }
    return MCSERVER_VANILLA_DATA_DIR;
}

} // namespace mcserver::protocol
