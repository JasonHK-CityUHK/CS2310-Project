add_executable(mcserver_tests
    net_ByteBuffer_test.cpp
    util_Md5_test.cpp
    protocol_Nbt_test.cpp
)

target_link_libraries(mcserver_tests PRIVATE
    mcserver_core
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(mcserver_tests)
