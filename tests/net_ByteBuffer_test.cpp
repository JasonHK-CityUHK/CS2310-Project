#include "mcserver/net/ByteBuffer.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <limits>

using namespace mcserver::net;

TEST_CASE("VarInt round-trips reference values", "[varint]") {
    // Reference encodings from the Java Edition protocol docs.
    struct Case {
        int32_t value;
        std::vector<uint8_t> bytes;
    };
    std::vector<Case> cases = {
        {0, {0x00}},
        {1, {0x01}},
        {2, {0x02}},
        {127, {0x7f}},
        {128, {0x80, 0x01}},
        {255, {0xff, 0x01}},
        {2097151, {0xff, 0xff, 0x7f}},
        {2147483647, {0xff, 0xff, 0xff, 0xff, 0x07}},
        {-1, {0xff, 0xff, 0xff, 0xff, 0x0f}},
        {-2147483648, {0x80, 0x80, 0x80, 0x80, 0x08}},
    };

    for (auto const& c : cases) {
        ByteWriter writer;
        writer.writeVarInt(c.value);
        REQUIRE(writer.size() == c.bytes.size());
        for (size_t i = 0; i < c.bytes.size(); ++i) {
            REQUIRE(static_cast<uint8_t>(writer.data()[i]) == c.bytes[i]);
        }

        ByteReader reader(std::span<const std::byte>(writer.data()));
        REQUIRE(reader.readVarInt() == c.value);
    }
}

TEST_CASE("VarLong round-trips extreme values", "[varint]") {
    std::vector<int64_t> values = {
        0, 1, -1, std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::min(), 123456789012345};
    for (int64_t v : values) {
        ByteWriter writer;
        writer.writeVarLong(v);
        ByteReader reader(std::span<const std::byte>(writer.data()));
        REQUIRE(reader.readVarLong() == v);
    }
}

TEST_CASE("String round-trip", "[string]") {
    ByteWriter writer;
    writer.writeString("hello world");
    ByteReader reader(std::span<const std::byte>(writer.data()));
    REQUIRE(reader.readString() == "hello world");
}

TEST_CASE("Fixed-width integers round-trip", "[primitives]") {
    ByteWriter writer;
    writer.writeBool(true);
    writer.writeByte(-5);
    writer.writeShort(-1234);
    writer.writeInt(-123456789);
    writer.writeLong(-1234567890123456789LL);
    writer.writeFloat(3.14159f);
    writer.writeDouble(2.718281828459045);

    ByteReader reader(std::span<const std::byte>(writer.data()));
    REQUIRE(reader.readBool() == true);
    REQUIRE(reader.readByte() == -5);
    REQUIRE(reader.readShort() == -1234);
    REQUIRE(reader.readInt() == -123456789);
    REQUIRE(reader.readLong() == -1234567890123456789LL);
    REQUIRE(reader.readFloat() == Catch::Approx(3.14159f));
    REQUIRE(reader.readDouble() == Catch::Approx(2.718281828459045));
}

TEST_CASE("Position packs and unpacks per protocol spec", "[position]") {
    BlockPos pos{.x = 18357644, .y = 831, .z = -20882616};
    ByteWriter writer;
    writer.writePosition(pos);
    ByteReader reader(std::span<const std::byte>(writer.data()));
    BlockPos out = reader.readPosition();
    REQUIRE(out.x == pos.x);
    REQUIRE(out.y == pos.y);
    REQUIRE(out.z == pos.z);
}

TEST_CASE("Buffer underrun throws", "[errors]") {
    ByteWriter writer;
    writer.writeByte(1);
    ByteReader reader(std::span<const std::byte>(writer.data()));
    reader.readByte();
    REQUIRE_THROWS_AS(reader.readByte(), BufferUnderrunError);
}
