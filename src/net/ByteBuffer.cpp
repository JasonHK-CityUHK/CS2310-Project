#include "mcserver/net/ByteBuffer.hpp"

#include <bit>
#include <cstring>

namespace mcserver::net {

namespace {
constexpr uint8_t kVarIntContinueBit = 0x80;
constexpr uint8_t kVarIntSegmentBits = 0x7F;
} // namespace

void ByteReader::requireBytes(size_t count) const {
    if (pos_ + count > data_.size()) { throw BufferUnderrunError(); }
}

std::byte ByteReader::readByteRaw() {
    requireBytes(1);
    return data_[pos_++];
}

uint8_t ByteReader::readUByte() { return static_cast<uint8_t>(readByteRaw()); }

int8_t ByteReader::readByte() { return static_cast<int8_t>(readByteRaw()); }

bool ByteReader::readBool() { return readUByte() != 0; }

int16_t ByteReader::readShort() {
    requireBytes(2);
    uint16_t value = (static_cast<uint16_t>(readUByte()) << 8) | static_cast<uint16_t>(readUByte());
    return static_cast<int16_t>(value);
}

uint16_t ByteReader::readUShort() { return static_cast<uint16_t>(readShort()); }

int32_t ByteReader::readInt() {
    requireBytes(4);
    uint32_t value = 0;
    for (int i = 0; i < 4; ++i) { value = (value << 8) | static_cast<uint32_t>(readUByte()); }
    return static_cast<int32_t>(value);
}

int64_t ByteReader::readLong() {
    requireBytes(8);
    uint64_t value = 0;
    for (int i = 0; i < 8; ++i) { value = (value << 8) | static_cast<uint64_t>(readUByte()); }
    return static_cast<int64_t>(value);
}

float ByteReader::readFloat() {
    int32_t bits = readInt();
    return std::bit_cast<float>(bits);
}

double ByteReader::readDouble() {
    int64_t bits = readLong();
    return std::bit_cast<double>(bits);
}

int32_t ByteReader::readVarInt() {
    uint32_t result = 0;
    int shift = 0;
    while (true) {
        uint8_t byte = readUByte();
        result |= static_cast<uint32_t>(byte & kVarIntSegmentBits) << shift;
        if ((byte & kVarIntContinueBit) == 0) { break; }
        shift += 7;
        if (shift >= 35) { throw MalformedVarIntError(); }
    }
    return static_cast<int32_t>(result);
}

int64_t ByteReader::readVarLong() {
    uint64_t result = 0;
    int shift = 0;
    while (true) {
        uint8_t byte = readUByte();
        result |= static_cast<uint64_t>(byte & kVarIntSegmentBits) << shift;
        if ((byte & kVarIntContinueBit) == 0) { break; }
        shift += 7;
        if (shift >= 70) { throw MalformedVarIntError(); }
    }
    return static_cast<int64_t>(result);
}

std::string ByteReader::readString() {
    int32_t length = readVarInt();
    if (length < 0) { throw MalformedVarIntError(); }
    requireBytes(static_cast<size_t>(length));
    std::string result(static_cast<size_t>(length), '\0');
    std::memcpy(result.data(), data_.data() + pos_, static_cast<size_t>(length));
    pos_ += static_cast<size_t>(length);
    return result;
}

std::vector<std::byte> ByteReader::readByteArray(size_t count) {
    requireBytes(count);
    std::vector<std::byte> result(data_.begin() + static_cast<ptrdiff_t>(pos_), data_.begin() + static_cast<ptrdiff_t>(pos_ + count));
    pos_ += count;
    return result;
}

std::vector<std::byte> ByteReader::readRemaining() {
    std::vector<std::byte> result(data_.begin() + static_cast<ptrdiff_t>(pos_), data_.end());
    pos_ = data_.size();
    return result;
}

std::array<std::byte, 16> ByteReader::readUuid() {
    std::array<std::byte, 16> uuid{};
    requireBytes(16);
    for (auto& b : uuid) { b = readByteRaw(); }
    return uuid;
}

BlockPos ByteReader::readPosition() {
    int64_t packed = readLong();
    int64_t x = packed >> 38;
    int64_t y = packed << 52 >> 52;
    int64_t z = packed << 26 >> 38;
    return BlockPos{static_cast<int32_t>(x), static_cast<int32_t>(y), static_cast<int32_t>(z)};
}

void ByteWriter::writeByteRaw(std::byte value) { buffer_.push_back(value); }

void ByteWriter::writeUByte(uint8_t value) { buffer_.push_back(static_cast<std::byte>(value)); }

void ByteWriter::writeByte(int8_t value) { writeUByte(static_cast<uint8_t>(value)); }

void ByteWriter::writeBool(bool value) { writeUByte(value ? 1 : 0); }

void ByteWriter::writeShort(int16_t value) {
    uint16_t bits = static_cast<uint16_t>(value);
    writeUByte(static_cast<uint8_t>(bits >> 8));
    writeUByte(static_cast<uint8_t>(bits & 0xFF));
}

void ByteWriter::writeUShort(uint16_t value) { writeShort(static_cast<int16_t>(value)); }

void ByteWriter::writeInt(int32_t value) {
    uint32_t bits = static_cast<uint32_t>(value);
    for (int shift = 24; shift >= 0; shift -= 8) { writeUByte(static_cast<uint8_t>(bits >> shift)); }
}

void ByteWriter::writeLong(int64_t value) {
    uint64_t bits = static_cast<uint64_t>(value);
    for (int shift = 56; shift >= 0; shift -= 8) { writeUByte(static_cast<uint8_t>(bits >> shift)); }
}

void ByteWriter::writeFloat(float value) { writeInt(std::bit_cast<int32_t>(value)); }

void ByteWriter::writeDouble(double value) { writeLong(std::bit_cast<int64_t>(value)); }

void ByteWriter::writeVarInt(int32_t value) {
    uint32_t bits = static_cast<uint32_t>(value);
    while (true) {
        if ((bits & ~static_cast<uint32_t>(kVarIntSegmentBits)) == 0) {
            writeUByte(static_cast<uint8_t>(bits));
            return;
        }
        writeUByte(static_cast<uint8_t>((bits & kVarIntSegmentBits) | kVarIntContinueBit));
        bits >>= 7;
    }
}

void ByteWriter::writeVarLong(int64_t value) {
    uint64_t bits = static_cast<uint64_t>(value);
    while (true) {
        if ((bits & ~static_cast<uint64_t>(kVarIntSegmentBits)) == 0) {
            writeUByte(static_cast<uint8_t>(bits));
            return;
        }
        writeUByte(static_cast<uint8_t>((bits & kVarIntSegmentBits) | kVarIntContinueBit));
        bits >>= 7;
    }
}

void ByteWriter::writeString(std::string_view value) {
    writeVarInt(static_cast<int32_t>(value.size()));
    buffer_.reserve(buffer_.size() + value.size());
    for (char c : value) { buffer_.push_back(static_cast<std::byte>(c)); }
}

void ByteWriter::writeBytes(std::span<const std::byte> bytes) {
    buffer_.insert(buffer_.end(), bytes.begin(), bytes.end());
}

void ByteWriter::writeUuid(std::array<std::byte, 16> const& uuid) {
    for (auto b : uuid) { writeByteRaw(b); }
}

void ByteWriter::writePosition(BlockPos const& pos) {
    uint64_t packed = ((static_cast<uint64_t>(pos.x) & 0x3FFFFFF) << 38)
                     | ((static_cast<uint64_t>(pos.z) & 0x3FFFFFF) << 12)
                     | (static_cast<uint64_t>(pos.y) & 0xFFF);
    writeLong(static_cast<int64_t>(packed));
}

size_t ByteWriter::varIntSize(int32_t value) noexcept {
    uint32_t bits = static_cast<uint32_t>(value);
    size_t count = 1;
    while ((bits & ~static_cast<uint32_t>(kVarIntSegmentBits)) != 0) {
        bits >>= 7;
        ++count;
    }
    return count;
}

} // namespace mcserver::net
