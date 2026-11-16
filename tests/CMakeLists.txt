add_executable(mcserver_tests
    server_AnvilWorld_test.cpp
    net_ByteBuffer_test.cpp
    util_Md5_test.cpp
    util_Logger_test.cpp
    protocol_Nbt_test.cpp
    server_ChunkData_test.cpp
    server_WorldStorage_test.cpp
    server_World_test.cpp
)

target_link_libraries(mcserver_tests PRIVATE
    mcserver_core
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(mcserver_tests)

find_package(Python3 QUIET COMPONENTS Interpreter)
if(UNIX AND Python3_Interpreter_FOUND)
    add_test(NAME world_persistence_tcp
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/world_persistence_smoke.py"
                "$<TARGET_FILE:mcserver>")
    set_tests_properties(world_persistence_tcp PROPERTIES TIMEOUT 90)
endif()
