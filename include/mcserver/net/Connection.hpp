#pragma once

#include "mcserver/net/ByteBuffer.hpp"
#include "mcserver/net/ProtocolState.hpp"

#include <asio.hpp>

#include <array>
#include <cstdint>
#include <deque>
#include <functional>
#include <memory>
#include <vector>

namespace mcserver::net {

// A single client's TCP connection: handles length-prefixed packet framing
// (uncompressed, per the project's offline/no-compression decision) and an
// outbound write queue. Game/protocol logic is supplied via callbacks so this
// class stays independent of packet semantics.
class Connection : public std::enable_shared_from_this<Connection> {
public:
    using PacketHandler = std::function<void(int32_t packetId, ByteReader& reader)>;
    using DisconnectHandler = std::function<void()>;

    explicit Connection(asio::ip::tcp::socket socket);

    void start();
    // Closes the socket; safe to call multiple times.
    void close();

    // Queues a packet for sending; safe to call from the connection's own handlers.
    void send(int32_t packetId, ByteWriter const& body);

    void setPacketHandler(PacketHandler handler) { onPacket_ = std::move(handler); }
    void setDisconnectHandler(DisconnectHandler handler) { onDisconnect_ = std::move(handler); }

    ProtocolState state() const noexcept { return state_; }
    void setState(ProtocolState state) noexcept { state_ = state; }

    asio::ip::tcp::socket& socket() noexcept { return socket_; }

private:
    void readNextLengthByte();
    void readBody(size_t length);
    void doWrite();
    void fail();

    asio::ip::tcp::socket socket_;
    ProtocolState state_ = ProtocolState::Handshaking;

    // VarInt length-prefix decode state.
    uint32_t lengthAccumulator_ = 0;
    int lengthShift_ = 0;
    std::array<std::byte, 1> lengthByteBuf_{};

    std::vector<std::byte> bodyBuf_;

    std::deque<std::vector<std::byte>> writeQueue_;
    bool writing_ = false;
    bool closed_ = false;

    PacketHandler onPacket_;
    DisconnectHandler onDisconnect_;
};

} // namespace mcserver::net
