#include "mcserver/protocol/Nbt.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace mcserver::protocol;

TEST_CASE("toJavaNetworkNbt round-trips and omits the root name", "[nbt]") {
    nbt::CompoundTag tag{
        {"a_byte", true},
        {"an_int", 42},
        {"a_float", 1.5f},
        {"a_string", std::string("hello")},
    };

    std::string encoded = toJavaNetworkNbt(tag);

    // Root compound: type byte (0x0A), then straight into the field list (no name length bytes).
    REQUIRE(static_cast<uint8_t>(encoded[0]) == 0x0A);
    REQUIRE(static_cast<uint8_t>(encoded[1]) != 0x00); // first field's own type byte, not a name-length byte

    nbt::CompoundTag decoded = fromJavaNetworkNbt(encoded);
    REQUIRE(decoded.contains("a_byte"));
    REQUIRE(decoded.contains("an_int"));
    REQUIRE(decoded.contains("a_float"));
    REQUIRE(decoded.contains("a_string"));
    REQUIRE(static_cast<int>(decoded["an_int"]) == 42);
    REQUIRE(static_cast<std::string const&>(decoded["a_string"]) == "hello");
}
