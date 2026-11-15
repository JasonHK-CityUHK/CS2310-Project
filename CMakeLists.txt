cmake_minimum_required(VERSION 3.24)
project(mcserver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MINECRAFT_VERSION "26.3" CACHE STRING "Minecraft version used for registry data")
set(MINECRAFT_SERVER_URL
    "https://piston-data.mojang.com/v1/objects/33680f5f2ac32864d6d7cf5e56a705fdb3e05f4c/server.jar"
    CACHE STRING "Official Minecraft server bundle URL")
set(MINECRAFT_SERVER_SHA1 "33680f5f2ac32864d6d7cf5e56a705fdb3e05f4c"
    CACHE STRING "SHA-1 of the official Minecraft server bundle")
set(MINECRAFT_DATA_STAMP "${CMAKE_BINARY_DIR}/minecraft-data.stamp")
set(MINECRAFT_REPORTS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/data")
set(MINECRAFT_REPORTS_DIR "${CMAKE_BINARY_DIR}/share/mcserver/data/reports")

foreach(report IN ITEMS blocks.json registries.json)
    if(NOT EXISTS "${MINECRAFT_REPORTS_SOURCE_DIR}/${report}")
        message(FATAL_ERROR "Required Minecraft data file is missing: ${MINECRAFT_REPORTS_SOURCE_DIR}/${report}")
    endif()
endforeach()

add_custom_command(
    OUTPUT "${MINECRAFT_DATA_STAMP}"
    COMMAND "${CMAKE_COMMAND}"
        -DMINECRAFT_VERSION=${MINECRAFT_VERSION}
        -DMINECRAFT_SERVER_URL=${MINECRAFT_SERVER_URL}
        -DMINECRAFT_SERVER_SHA1=${MINECRAFT_SERVER_SHA1}
        -DMINECRAFT_REPORTS_SOURCE_DIR=${MINECRAFT_REPORTS_SOURCE_DIR}
        -DMINECRAFT_REPORTS_DIR=${MINECRAFT_REPORTS_DIR}
        -DMINECRAFT_DATA_STAMP=${MINECRAFT_DATA_STAMP}
        -P "${CMAKE_SOURCE_DIR}/cmake/DownloadMinecraftData.cmake"
    COMMENT "Preparing Minecraft ${MINECRAFT_VERSION} runtime data"
    DEPENDS
        "${CMAKE_SOURCE_DIR}/cmake/DownloadMinecraftData.cmake"
        "${MINECRAFT_REPORTS_SOURCE_DIR}/blocks.json"
        "${MINECRAFT_REPORTS_SOURCE_DIR}/registries.json"
    VERBATIM
)
add_custom_target(mcserver_data DEPENDS "${MINECRAFT_DATA_STAMP}")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

find_package(ZLIB REQUIRED)

include(cmake/Dependencies.cmake)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
