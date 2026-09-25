#pragma once

#include <nbt/NBT.hpp>

#include <string>
#include <string_view>

namespace mcserver::protocol {

// Encodes/decodes the Java Edition protocol's "NBT" wire type: standard big-endian
// binary NBT, but (since 1.20.2) with the root compound's name omitted entirely
// (just the type byte, then straight into the field list). GlacieTeam/NBT's own
// toBinaryNbt()/toNetworkNbt() don't produce this exact layout (the former always
// writes an empty name string, the latter targets Bedrock's varint-based format),
// so we splice the 2-byte empty-name length out of toBinaryNbt(false) ourselves.
[[nodiscard]] std::string toJavaNetworkNbt(nbt::CompoundTag const& tag);
[[nodiscard]] std::string toJavaNetworkNbt(nbt::CompoundTagVariant const& tag);
[[nodiscard]] nbt::CompoundTag fromJavaNetworkNbt(std::string_view data);

} // namespace mcserver::protocol
