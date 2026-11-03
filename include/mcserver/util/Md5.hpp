#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace mcserver::util {

// Minimal MD5 implementation (RFC 1321), used only to derive offline-mode
// player UUIDs the same way vanilla does: UUID.nameUUIDFromBytes("OfflinePlayer:" + name).
[[nodiscard]] std::array<uint8_t, 16> md5(std::string_view input);

// Builds a version-3 (name-based) UUID from raw MD5 bytes, matching
// java.util.UUID.nameUUIDFromBytes, and returns it as 16 big-endian bytes
// ready to write on the wire.
[[nodiscard]] std::array<std::byte, 16> offlinePlayerUuid(std::string_view playerName);

} // namespace mcserver::util
