#include "mcserver/util/Md5.hpp"

#include <catch2/catch_test_macros.hpp>
#include <iomanip>
#include <sstream>

using namespace mcserver::util;

namespace {
std::string toHex(std::array<uint8_t, 16> const& bytes) {
    std::ostringstream oss;
    for (auto b : bytes) { oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(b); }
    return oss.str();
}
} // namespace

TEST_CASE("md5 matches known test vectors", "[md5]") {
    // Reference digests from RFC 1321, Appendix A.5.
    REQUIRE(toHex(md5("")) == "d41d8cd98f00b204e9800998ecf8427e");
    REQUIRE(toHex(md5("abc")) == "900150983cd24fb0d6963f7d28e17f72");
    REQUIRE(toHex(md5("message digest")) == "f96b697d7cb7938d525a2f31aaf161d0");
    REQUIRE(
        toHex(md5("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"))
        == "76658de2ac7d406f93dfbe8bb6d9f549"
    );
}

TEST_CASE("offlinePlayerUuid matches vanilla's OfflinePlayer:Notch UUID", "[uuid]") {
    // Reference value independently computed as:
    // md5("OfflinePlayer:Notch") with RFC 4122 v3 version/variant bits applied.
    auto uuid = offlinePlayerUuid("Notch");
    std::ostringstream oss;
    for (auto b : uuid) { oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<uint8_t>(b)); }
    REQUIRE(oss.str() == "b50ad385829d3141a2167e7d7539ba7f");
}
