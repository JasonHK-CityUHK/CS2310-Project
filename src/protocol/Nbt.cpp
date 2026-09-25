#include "mcserver/protocol/Nbt.hpp"

#include <stdexcept>

namespace mcserver::protocol {

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

} // namespace mcserver::protocol
