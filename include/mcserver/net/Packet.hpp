#pragma once

#include "mcserver/net/ByteBuffer.hpp"

#include <cstdint>

namespace mcserver::net {

// Encodes `packetId` + `body` as a length-prefixed protocol frame
// (VarInt total length, VarInt packet ID, payload), uncompressed.
[[nodiscard]] std::vector<std::byte> frameOutboundPacket(int32_t packetId, ByteWriter const& body);

} // namespace mcserver::net
