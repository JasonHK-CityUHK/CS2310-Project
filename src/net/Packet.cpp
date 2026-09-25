#include "mcserver/net/Packet.hpp"

namespace mcserver::net {

std::vector<std::byte> frameOutboundPacket(int32_t packetId, ByteWriter const& body) {
    ByteWriter inner;
    inner.writeVarInt(packetId);
    inner.writeBytes(body.data());

    ByteWriter frame;
    frame.writeVarInt(static_cast<int32_t>(inner.size()));
    frame.writeBytes(inner.data());
    return frame.take();
}

} // namespace mcserver::net
