add_library(mcserver_core
    net/ByteBuffer.cpp
    net/Packet.cpp
    net/Connection.cpp
    util/Md5.cpp
    protocol/Nbt.cpp
    protocol/JsonToNbt.cpp
    protocol/Registries.cpp
    protocol/Tags.cpp
    server/ClientSession.cpp
    server/Server.cpp
)
add_dependencies(mcserver_core mcserver_data)

target_include_directories(mcserver_core PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(mcserver_core PUBLIC
    asio
    glacie_nbt
    nlohmann_json::nlohmann_json
)

target_compile_features(mcserver_core PUBLIC cxx_std_23)

# Points the registry and tag loaders at build-time data extracted from the official
# Minecraft server bundle.
target_compile_definitions(mcserver_core PRIVATE
    MCSERVER_REGISTRY_DATA_DIR="${CMAKE_BINARY_DIR}/share/mcserver/registries"
    MCSERVER_TAG_DATA_DIR="${CMAKE_BINARY_DIR}/share/mcserver/data/minecraft/tags"
    MCSERVER_VANILLA_DATA_DIR="${CMAKE_BINARY_DIR}/share/mcserver/data/minecraft"
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(mcserver_core PRIVATE -Wall -Wextra)
endif()

add_executable(mcserver main.cpp)
target_link_libraries(mcserver PRIVATE mcserver_core)
