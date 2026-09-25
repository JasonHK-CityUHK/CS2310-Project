#include "mcserver/protocol/Nbt.hpp"

#include <stdexcept>

namespace mcserver::protocol {

std::string toJavaNetworkNbt(nbt::CompoundTag const& tag) {
    std::string full = tag.toBinaryNbt(/*isLittleEndian=*/false);
    if (full.size() < 3) { throw std::runtime_error("unexpected empty binary NBT payload"); }
    std::string result;
    result.reserve(full.size() - 2);
    result += full[0]; // type byte
    result.append(full.begin() + 3, full.end()); // skip the 2-byte (empty) root name length
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
