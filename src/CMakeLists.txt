add_library(mcserver_core
    net/ByteBuffer.cpp
    net/Packet.cpp
    net/Connection.cpp
    util/Md5.cpp
    util/Logger.cpp
    protocol/Nbt.cpp
    protocol/JsonToNbt.cpp
    protocol/Registries.cpp
    protocol/Tags.cpp
    server/ChunkData.cpp
    server/ClientSession.cpp
    server/JavaWorld.cpp
    server/LevelData.cpp
    server/RegionFile.cpp
    server/SectionData.cpp
    server/Server.cpp
    server/ServerProperties.cpp
    server/WorldStorage.cpp
    server/WorldLock.cpp
    server/World.cpp
)
add_dependencies(mcserver_core mcserver_data)

target_include_directories(mcserver_core PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(mcserver_core PUBLIC
    asio
    glacie_nbt
    nlohmann_json::nlohmann_json
    ZLIB::ZLIB
    mcserver_lz4
)

target_compile_features(mcserver_core PUBLIC cxx_std_23)

# Points registry, tag, vanilla-data, and report loaders at build-time data.
target_compile_definitions(mcserver_core PRIVATE
    MCSERVER_REGISTRY_DATA_DIR="${CMAKE_BINARY_DIR}/share/mcserver/registries"
    MCSERVER_TAG_DATA_DIR="${CMAKE_BINARY_DIR}/share/mcserver/data/minecraft/tags"
    MCSERVER_VANILLA_DATA_DIR="${CMAKE_BINARY_DIR}/share/mcserver/data/minecraft"
    MCSERVER_VANILLA_REPORTS_DIR="${CMAKE_BINARY_DIR}/share/mcserver/data/reports"
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(mcserver_core PRIVATE -Wall -Wextra)
endif()

add_executable(mcserver main.cpp)
target_link_libraries(mcserver PRIVATE mcserver_core)
