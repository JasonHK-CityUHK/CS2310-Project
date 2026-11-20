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

TEST_CASE("Java disk NBT validates named root and malformed input", "[nbt][disk-nbt]") {
    nbt::CompoundTag tag{{"value", 42}};
    auto data = tag.toBinaryNbt(false);
    REQUIRE(static_cast<int>(fromJavaDiskNbt(data)["value"]) == 42);
    REQUIRE_THROWS(fromJavaDiskNbt(data.substr(0, data.size() - 1)));
    REQUIRE_THROWS(fromJavaDiskNbt(data + '\0'));
    REQUIRE_THROWS(fromJavaDiskNbt(std::string("\x01\0\0", 3)));
    REQUIRE_THROWS(fromJavaDiskNbt(std::string("\x0a\0\0\x09\0\x01x\x01\xff\xff\xff\xff\0", 13)));
    std::string longName("\x0a\x80\x00", 3);
    longName.append(32768, 'a');
    longName.push_back('\0');
    REQUIRE_THROWS(fromJavaDiskNbt(longName));
}
