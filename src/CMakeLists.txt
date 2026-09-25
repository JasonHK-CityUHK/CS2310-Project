add_library(mcserver_core
    net/ByteBuffer.cpp
    net/Packet.cpp
    net/Connection.cpp
    util/Md5.cpp
    protocol/Nbt.cpp
    protocol/Registries.cpp
    server/ClientSession.cpp
    server/Server.cpp
)

target_include_directories(mcserver_core PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(mcserver_core PUBLIC
    asio
    glacie_nbt
)

target_compile_features(mcserver_core PUBLIC cxx_std_23)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(mcserver_core PRIVATE -Wall -Wextra)
endif()

add_executable(mcserver main.cpp)
target_link_libraries(mcserver PRIVATE mcserver_core)
