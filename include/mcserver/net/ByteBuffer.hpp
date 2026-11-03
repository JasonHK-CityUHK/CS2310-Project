#pragma once

#include <array>
#include <cstdint>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace mcserver::net {

// A block position packed the way the protocol's "Position" type expects (x:26, z:26, y:12 bits).
struct BlockPos {
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
};

// Thrown when a read runs past the end of the available bytes.
class BufferUnderrunError : public std::runtime_error {
public:
    BufferUnderrunError() : std::runtime_error("buffer underrun while reading packet") {}
};

// Thrown when a VarInt/VarLong is malformed (too many continuation bytes).
class MalformedVarIntError : public std::runtime_error {
public:
    MalformedVarIntError() : std::runtime_error("VarInt/VarLong is too long") {}
};

// Reads Minecraft protocol primitive types from a fixed byte span, advancing a cursor.
class ByteReader {
public:
    explicit ByteReader(std::span<const std::byte> data) : data_(data) {}

    [[nodiscard]] size_t remaining() const noexcept { return data_.size() - pos_; }
    [[nodiscard]] size_t position() const noexcept { return pos_; }

    std::byte readByteRaw();
    uint8_t readUByte();
    int8_t readByte();
    bool readBool();
    int16_t readShort();
    uint16_t readUShort();
    int32_t readInt();
    int64_t readLong();
    float readFloat();
    double readDouble();

    int32_t readVarInt();
    int64_t readVarLong();

    std::string readString();
    std::vector<std::byte> readByteArray(size_t count);
    // Reads the rest of the buffer (used for the trailing byte array in some packets).
    std::vector<std::byte> readRemaining();

    // 16-byte UUID, encoded as two big-endian longs (most significant first).
    std::array<std::byte, 16> readUuid();
    BlockPos readPosition();

private:
    std::span<const std::byte> data_;
    size_t pos_ = 0;

    void requireBytes(size_t count) const;
};

// Writes Minecraft protocol primitive types into a growable byte buffer.
class ByteWriter {
public:
    void writeByteRaw(std::byte value);
    void writeUByte(uint8_t value);
    void writeByte(int8_t value);
    void writeBool(bool value);
    void writeShort(int16_t value);
    void writeUShort(uint16_t value);
    void writeInt(int32_t value);
    void writeLong(int64_t value);
    void writeFloat(float value);
    void writeDouble(double value);

    void writeVarInt(int32_t value);
    void writeVarLong(int64_t value);

    void writeString(std::string_view value);
    void writeBytes(std::span<const std::byte> bytes);

    void writeUuid(std::array<std::byte, 16> const& uuid);
    void writePosition(BlockPos const& pos);

    [[nodiscard]] const std::vector<std::byte>& data() const noexcept { return buffer_; }
    [[nodiscard]] std::vector<std::byte> take() noexcept { return std::move(buffer_); }
    [[nodiscard]] size_t size() const noexcept { return buffer_.size(); }

    // Number of bytes a VarInt encoding of `value` would occupy.
    static size_t varIntSize(int32_t value) noexcept;

private:
    std::vector<std::byte> buffer_;
};

} // namespace mcserver::net
