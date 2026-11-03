#pragma once

#include <nbt/NBT.hpp>
#include <nlohmann/json_fwd.hpp>

namespace mcserver::protocol {

// Converts a JSON value into the equivalent NBT representation.
//
// GlacieTeam/NBT ships its own CompoundTag::fromJson(), but it encodes every
// JSON integer as a ByteTag without range-checking, silently wrapping values
// outside [-128, 127] (e.g. 384 becomes -128, 6000 becomes 112). Real vanilla
// registry data is full of such values, so we do our own conversion instead:
// integers always become IntTag (or LongTag if they don't fit in 32 bits) and
// booleans always become ByteTag(0/1), matching what the game's NBT codecs
// (which coerce numeric tag types leniently) actually expect.
[[nodiscard]] nbt::CompoundTagVariant jsonValueToNbt(nlohmann::json const& value);
[[nodiscard]] nbt::CompoundTag jsonToNbt(nlohmann::json const& object);

} // namespace mcserver::protocol
