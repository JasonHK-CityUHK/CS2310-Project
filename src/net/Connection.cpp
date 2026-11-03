#include "mcserver/net/Connection.hpp"

namespace mcserver::net {

namespace {
constexpr uint8_t kVarIntContinueBit = 0x80;
constexpr uint8_t kVarIntSegmentBits = 0x7F;
constexpr int kMaxVarIntShift = 35; // 5 bytes max for a packet-length VarInt
} // namespace

Connection::Connection(asio::ip::tcp::socket socket) : socket_(std::move(socket)) {}

void Connection::start() { readNextLengthByte(); }

void Connection::close() {
    if (closed_) { return; }
    closed_ = true;
    asio::error_code ignored;
    socket_.shutdown(asio::ip::tcp::socket::shutdown_both, ignored);
    socket_.close(ignored);
}

void Connection::fail() {
    if (closed_) { return; }
    close();
    if (onDisconnect_) { onDisconnect_(); }
}

void Connection::readNextLengthByte() {
    auto self = shared_from_this();
    asio::async_read(
        socket_,
        asio::buffer(lengthByteBuf_),
        [this, self](asio::error_code ec, size_t /*n*/) {
            if (ec) {
                fail();
                return;
            }
            uint8_t byte = static_cast<uint8_t>(lengthByteBuf_[0]);
            lengthAccumulator_ |= static_cast<uint32_t>(byte & kVarIntSegmentBits) << lengthShift_;
            if ((byte & kVarIntContinueBit) == 0) {
                size_t length = lengthAccumulator_;
                lengthAccumulator_ = 0;
                lengthShift_ = 0;
                if (length == 0) {
                    // Zero-length frames are not valid packets; treat as protocol error.
                    fail();
                    return;
                }
                readBody(length);
                return;
            }
            lengthShift_ += 7;
            if (lengthShift_ >= kMaxVarIntShift) {
                fail();
                return;
            }
            readNextLengthByte();
        }
    );
}

void Connection::readBody(size_t length) {
    bodyBuf_.assign(length, std::byte{0});
    auto self = shared_from_this();
    asio::async_read(
        socket_,
        asio::buffer(bodyBuf_.data(), bodyBuf_.size()),
        [this, self](asio::error_code ec, size_t /*n*/) {
            if (ec) {
                fail();
                return;
            }
            ByteReader reader{std::span<const std::byte>(bodyBuf_)};
            try {
                int32_t packetId = reader.readVarInt();
                if (onPacket_) { onPacket_(packetId, reader); }
            } catch (std::exception const&) {
                fail();
                return;
            }
            if (!closed_) { readNextLengthByte(); }
        }
    );
}

void Connection::send(int32_t packetId, ByteWriter const& body) {
    if (closed_) { return; }
    ByteWriter inner;
    inner.writeVarInt(packetId);
    inner.writeBytes(body.data());
    ByteWriter frame;
    frame.writeVarInt(static_cast<int32_t>(inner.size()));
    frame.writeBytes(inner.data());

    auto self = shared_from_this();
    bool wasEmpty = writeQueue_.empty();
    writeQueue_.push_back(frame.take());
    if (!writing_ && wasEmpty) { doWrite(); }
}

void Connection::doWrite() {
    if (writeQueue_.empty()) {
        writing_ = false;
        return;
    }
    writing_ = true;
    auto self = shared_from_this();
    asio::async_write(
        socket_,
        asio::buffer(writeQueue_.front()),
        [this, self](asio::error_code ec, size_t /*n*/) {
            if (ec) {
                fail();
                return;
            }
            writeQueue_.pop_front();
            doWrite();
        }
    );
}

} // namespace mcserver::net
