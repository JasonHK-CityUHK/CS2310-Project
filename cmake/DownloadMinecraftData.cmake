cmake_minimum_required(VERSION 3.24)

set(server_jar "${CMAKE_BINARY_DIR}/minecraft-server-${MINECRAFT_VERSION}.jar")
set(outer_dir "${CMAKE_BINARY_DIR}/minecraft-server-outer")
set(inner_dir "${CMAKE_BINARY_DIR}/minecraft-server-inner")
set(vanilla_data_dir "${CMAKE_BINARY_DIR}/share/mcserver/data/minecraft")
set(registry_data_dir "${CMAKE_BINARY_DIR}/share/mcserver/registries")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}")
file(DOWNLOAD "${MINECRAFT_SERVER_URL}" "${server_jar}"
    EXPECTED_HASH "SHA1=${MINECRAFT_SERVER_SHA1}"
    SHOW_PROGRESS
    TLS_VERIFY ON
    STATUS download_status
)
list(GET download_status 0 download_code)
if(NOT download_code EQUAL 0)
    message(FATAL_ERROR "Failed to download Minecraft ${MINECRAFT_VERSION}: ${download_status}")
endif()

file(REMOVE_RECURSE "${outer_dir}" "${inner_dir}" "${vanilla_data_dir}" "${registry_data_dir}")
file(MAKE_DIRECTORY "${outer_dir}" "${inner_dir}")

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E tar xf "${server_jar}"
    WORKING_DIRECTORY "${outer_dir}"
    RESULT_VARIABLE outer_extract_code
)
if(NOT outer_extract_code EQUAL 0)
    message(FATAL_ERROR "Failed to extract the outer Minecraft server bundle")
endif()

file(GLOB_RECURSE inner_jars LIST_DIRECTORIES false
    "${outer_dir}/META-INF/versions/*/server-*.jar")
list(LENGTH inner_jars inner_jar_count)
if(inner_jar_count EQUAL 0)
    message(FATAL_ERROR "Could not find the nested server jar in ${server_jar}")
endif()
list(GET inner_jars 0 inner_jar)

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E tar xf "${inner_jar}"
    WORKING_DIRECTORY "${inner_dir}"
    RESULT_VARIABLE inner_extract_code
)
if(NOT inner_extract_code EQUAL 0)
    message(FATAL_ERROR "Failed to extract the nested Minecraft server jar")
endif()

file(COPY "${inner_dir}/data/minecraft/" DESTINATION "${vanilla_data_dir}")

set(registry_roots
    banner_pattern cat_sound_variant cat_variant chat_type chicken_sound_variant
    chicken_variant cow_sound_variant cow_variant damage_type dialog dimension_type
    enchantment frog_variant instrument jukebox_song painting_variant pig_sound_variant
    pig_variant sulfur_cube_archetype test_environment test_instance timeline
    trim_material trim_pattern wolf_sound_variant wolf_variant world_clock
    zombie_nautilus_variant
)
file(MAKE_DIRECTORY "${registry_data_dir}")
foreach(registry_root IN LISTS registry_roots)
    file(COPY "${inner_dir}/data/minecraft/${registry_root}/"
        DESTINATION "${registry_data_dir}/${registry_root}")
endforeach()
file(COPY "${inner_dir}/data/minecraft/worldgen/biome/"
    DESTINATION "${registry_data_dir}/worldgen/biome")

file(TOUCH "${MINECRAFT_DATA_STAMP}")
