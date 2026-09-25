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

target_include_directories(mcserver_core PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(mcserver_core PUBLIC
    asio
    glacie_nbt
    nlohmann_json::nlohmann_json
)

target_compile_features(mcserver_core PUBLIC cxx_std_23)

# Points the registry loader at the real vanilla registry JSON bundled in data/registries/
# (see repo memory for how it was extracted from the client jar). Dev-mode: points straight
# at the source tree rather than an installed copy.
target_compile_definitions(mcserver_core PRIVATE
    MCSERVER_REGISTRY_DATA_DIR="${CMAKE_SOURCE_DIR}/data/registries"
    MCSERVER_TAG_DATA_DIR="${CMAKE_SOURCE_DIR}/share/data/minecraft/tags"
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(mcserver_core PRIVATE -Wall -Wextra)
endif()

add_executable(mcserver main.cpp)
target_link_libraries(mcserver PRIVATE mcserver_core)
