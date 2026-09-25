#include "mcserver/util/Md5.hpp"

#include <cstring>
#include <string>
#include <vector>

namespace mcserver::util {

namespace {

constexpr uint32_t leftRotate(uint32_t x, uint32_t c) { return (x << c) | (x >> (32 - c)); }

// Per-round shift amounts and sine-derived constants from RFC 1321.
constexpr std::array<uint32_t, 64> kShifts = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

constexpr std::array<uint32_t, 64> kConstants = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
    0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
    0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97,
    0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

} // namespace

std::array<uint8_t, 16> md5(std::string_view input) {
    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xefcdab89;
    uint32_t c0 = 0x98badcfe;
    uint32_t d0 = 0x10325476;

    std::vector<uint8_t> msg(input.begin(), input.end());
    uint64_t originalBitLen = static_cast<uint64_t>(msg.size()) * 8;

    msg.push_back(0x80);
    while (msg.size() % 64 != 56) { msg.push_back(0x00); }
    for (int i = 0; i < 8; ++i) { msg.push_back(static_cast<uint8_t>(originalBitLen >> (8 * i))); }

    for (size_t chunkStart = 0; chunkStart < msg.size(); chunkStart += 64) {
        std::array<uint32_t, 16> m{};
        for (int i = 0; i < 16; ++i) {
            m[static_cast<size_t>(i)] = static_cast<uint32_t>(msg[chunkStart + static_cast<size_t>(i) * 4])
                                       | (static_cast<uint32_t>(msg[chunkStart + static_cast<size_t>(i) * 4 + 1]) << 8)
                                       | (static_cast<uint32_t>(msg[chunkStart + static_cast<size_t>(i) * 4 + 2]) << 16)
                                       | (static_cast<uint32_t>(msg[chunkStart + static_cast<size_t>(i) * 4 + 3]) << 24);
        }

        uint32_t a = a0, b = b0, c = c0, d = d0;
        for (uint32_t i = 0; i < 64; ++i) {
            uint32_t f, g;
            if (i < 16) {
                f = (b & c) | (~b & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | (~d & c);
                g = (5 * i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3 * i + 5) % 16;
            } else {
                f = c ^ (b | ~d);
                g = (7 * i) % 16;
            }
            f = f + a + kConstants[i] + m[g];
            a = d;
            d = c;
            c = b;
            b = b + leftRotate(f, kShifts[i]);
        }
        a0 += a;
        b0 += b;
        c0 += c;
        d0 += d;
    }

    std::array<uint8_t, 16> digest{};
    auto writeLe = [&digest](size_t offset, uint32_t value) {
        digest[offset] = static_cast<uint8_t>(value);
        digest[offset + 1] = static_cast<uint8_t>(value >> 8);
        digest[offset + 2] = static_cast<uint8_t>(value >> 16);
        digest[offset + 3] = static_cast<uint8_t>(value >> 24);
    };
    writeLe(0, a0);
    writeLe(4, b0);
    writeLe(8, c0);
    writeLe(12, d0);
    return digest;
}

std::array<std::byte, 16> offlinePlayerUuid(std::string_view playerName) {
    std::string source = "OfflinePlayer:";
    source += playerName;
    std::array<uint8_t, 16> bytes = md5(source);

    // Apply RFC 4122 version 3 (name-based, MD5) and variant bits, per java.util.UUID.nameUUIDFromBytes.
    bytes[6] = static_cast<uint8_t>((bytes[6] & 0x0F) | 0x30);
    bytes[8] = static_cast<uint8_t>((bytes[8] & 0x3F) | 0x80);

    std::array<std::byte, 16> result{};
    for (size_t i = 0; i < 16; ++i) { result[i] = static_cast<std::byte>(bytes[i]); }
    return result;
}

} // namespace mcserver::util
