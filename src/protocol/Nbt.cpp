#include "mcserver/protocol/Nbt.hpp"

#include <stdexcept>

namespace mcserver::protocol {
namespace {

class DiskNbtValidator {
public:
    explicit DiskNbtValidator(std::string_view data) : data_(data) {}

    void validate() {
        if (readByte() != 10) { throw std::runtime_error("NBT root must be a compound"); }
        skipString();
        readPayload(10, 0);
        if (position_ != data_.size()) { throw std::runtime_error("trailing bytes in NBT"); }
    }

private:
    uint8_t readByte() {
        if (position_ == data_.size()) { throw std::runtime_error("truncated NBT"); }
        return static_cast<uint8_t>(data_[position_++]);
    }

    uint32_t readInteger(size_t width) {
        uint32_t result = 0;
        for (size_t index = 0; index < width; ++index) { result = (result << 8) | readByte(); }
        return result;
    }

    void skip(size_t count) {
        if (count > data_.size() - position_) { throw std::runtime_error("truncated NBT"); }
        position_ += count;
    }

    void skipString() {
        uint32_t length = readInteger(2);
        if (length > 32767) { throw std::runtime_error("NBT string exceeds parser limit"); }
        skip(length);
    }

    size_t readCount() {
        uint32_t count = readInteger(4);
        if (count > 0x7fffffff) { throw std::runtime_error("negative NBT length"); }
        return count;
    }

    void readPayload(uint8_t type, size_t depth) {
        if (depth > 64) { throw std::runtime_error("NBT nesting limit exceeded"); }
        if (++tagCount_ > 1000000) { throw std::runtime_error("NBT tag count limit exceeded"); }
        switch (type) {
        case 1: skip(1); break;
        case 2: skip(2); break;
        case 3: case 5: skip(4); break;
        case 4: case 6: skip(8); break;
        case 7: skip(readCount()); break;
        case 8: skipString(); break;
        case 9: {
            uint8_t elementType = readByte();
            size_t count = readCount();
            if (elementType > 12 || (elementType == 0 && count != 0) || count > data_.size()) {
                throw std::runtime_error("invalid NBT list");
            }
            for (size_t index = 0; index < count; ++index) { readPayload(elementType, depth + 1); }
            break;
        }
        case 10:
            while (true) {
                uint8_t childType = readByte();
                if (childType == 0) { break; }
                skipString();
                readPayload(childType, depth + 1);
            }
            break;
        case 11: case 12: {
            size_t count = readCount();
            size_t width = type == 11 ? 4 : 8;
            if (count > (data_.size() - position_) / width) { throw std::runtime_error("truncated NBT array"); }
            skip(count * width);
            break;
        }
        default: throw std::runtime_error("invalid NBT tag type");
        }
    }

    std::string_view data_;
    size_t position_ = 0;
    size_t tagCount_ = 0;
};

} // namespace

std::string toJavaNetworkNbt(nbt::CompoundTag const& tag) {
    return toJavaNetworkNbt(nbt::CompoundTagVariant(tag));
}

std::string toJavaNetworkNbt(nbt::CompoundTagVariant const& tag) {
    std::string result;
    nbt::io::BytesDataOutput stream(result, false, false);
    stream.writeByte(static_cast<uint8_t>(tag->getType()));
    tag->write(stream);
    return result;
}

nbt::CompoundTag fromJavaNetworkNbt(std::string_view data) {
    if (data.empty()) { throw std::runtime_error("empty NBT payload"); }
    std::string reconstructed;
    reconstructed.reserve(data.size() + 2);
    reconstructed += data[0]; // type byte
    reconstructed += '\0';
    reconstructed += '\0'; // re-insert the empty root name length GlacieTeam/NBT expects
    reconstructed.append(data.begin() + 1, data.end());
    return nbt::CompoundTag::fromBinaryNbt(reconstructed, /*isLittleEndian=*/false);
}

nbt::CompoundTag fromJavaDiskNbt(std::string_view data) {
    DiskNbtValidator(data).validate();
    return nbt::CompoundTag::fromBinaryNbt(data, /*isLittleEndian=*/false);
}

} // namespace mcserver::protocol
