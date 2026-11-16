include(FetchContent)
set(FETCHCONTENT_QUIET ON)

# --- asio (standalone, header-only) -----------------------------------------
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-38-2
    GIT_SHALLOW TRUE
)
FetchContent_Populate(asio)

add_library(asio INTERFACE)
target_include_directories(asio SYSTEM INTERFACE "${asio_SOURCE_DIR}/asio/include")
target_compile_definitions(asio INTERFACE ASIO_STANDALONE ASIO_NO_DEPRECATED)
find_package(Threads REQUIRED)
target_link_libraries(asio INTERFACE Threads::Threads)

# --- GlacieTeam/BinaryStream (no CMake build of its own) --------------------
FetchContent_Declare(
    binarystream
    GIT_REPOSITORY https://github.com/GlacieTeam/BinaryStream.git
    GIT_TAG v2.3.2
    GIT_SHALLOW TRUE
)
FetchContent_Populate(binarystream)

file(GLOB_RECURSE BINARYSTREAM_SOURCES CONFIGURE_DEPENDS "${binarystream_SOURCE_DIR}/src/binarystream/*.cpp")
add_library(binarystream STATIC ${BINARYSTREAM_SOURCES})
target_include_directories(binarystream SYSTEM PUBLIC "${binarystream_SOURCE_DIR}/include")
target_compile_features(binarystream PUBLIC cxx_std_23)

# --- GlacieTeam/NBT (no CMake build of its own) ------------------------------
FetchContent_Declare(
    glacie_nbt
    GIT_REPOSITORY https://github.com/GlacieTeam/NBT.git
    GIT_TAG v2.6.3
    GIT_SHALLOW TRUE
)
FetchContent_Populate(glacie_nbt)

file(GLOB_RECURSE GLACIE_NBT_SOURCES CONFIGURE_DEPENDS "${glacie_nbt_SOURCE_DIR}/src/nbt/*.cpp")
add_library(glacie_nbt STATIC ${GLACIE_NBT_SOURCES})
target_include_directories(glacie_nbt SYSTEM PUBLIC "${glacie_nbt_SOURCE_DIR}/include")
target_include_directories(glacie_nbt PRIVATE "${glacie_nbt_SOURCE_DIR}/src")
target_compile_features(glacie_nbt PUBLIC cxx_std_23)
target_link_libraries(glacie_nbt PUBLIC binarystream ZLIB::ZLIB)

# --- nlohmann/json (used for our own JSON->NBT conversion; GlacieTeam/NBT's
# built-in fromJson() has an integer-width bug — see repo memory) ------------
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_SHALLOW TRUE
)
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(nlohmann_json)

# --- Catch2 (test framework) -------------------------------------------------
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.16.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Catch2)
