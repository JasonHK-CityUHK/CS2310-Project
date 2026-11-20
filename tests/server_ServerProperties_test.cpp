#include "mcserver/server/ServerProperties.hpp"

#include <catch2/catch_test_macros.hpp>

#include <sstream>

using mcserver::server::parseServerProperties;

TEST_CASE("Server properties use defaults and ignore unsupported keys", "[properties]") {
    std::istringstream input("# comment\nunknown=\\uNOPE\n");
    auto settings = parseServerProperties(input);
    REQUIRE(settings.serverIp.empty());
    REQUIRE(settings.serverPort == 25565);
    REQUIRE(settings.viewDistance == 10);
    REQUIRE(settings.motd == "CS2310 minimal MC server");
    REQUIRE(settings.levelName == "world");
}

TEST_CASE("Server properties parse Java escapes and continuations", "[properties]") {
    std::istringstream input("! comment\\\nserver-ip=127.0.0.1\nserver-port : 25566\n"
                             "view-distance=32\n"
                             "motd=Hello\\\n  world\\u0021 \\uD83D\\uDE00\n"
                             "level\\-name worlds\\/my\\ world\n");
    auto settings = parseServerProperties(input);
    REQUIRE(settings.serverIp == "127.0.0.1");
    REQUIRE(settings.serverPort == 25566);
    REQUIRE(settings.viewDistance == 32);
    REQUIRE(settings.motd == "Helloworld! \xF0\x9F\x98\x80");
    REQUIRE(settings.levelName == "worlds/my world");
}

TEST_CASE("Server properties reject invalid supported values", "[properties]") {
    for (auto const* text : {"server-port=0", "server-port=65536", "server-port=abc",
                             "view-distance=2", "view-distance=33", "view-distance=-1",
                             "view-distance=3x",
                             "server-ip=not-an-ip", "level-name=", "motd=\\uNOPE",
                             "motd=\\uD800"}) {
        std::istringstream input(text);
        REQUIRE_THROWS(parseServerProperties(input));
    }
}
