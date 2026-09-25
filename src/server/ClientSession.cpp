#include "mcserver/server/ClientSession.hpp"
#include "mcserver/protocol/Nbt.hpp"
#include "mcserver/protocol/Registries.hpp"
#include "mcserver/util/Md5.hpp"

#include <iostream>
#include <span>

namespace mcserver::server {

using net::ByteReader;
using net::ByteWriter;
using net::ProtocolState;

namespace {
// Packet IDs below are taken from references/minecraft-wiki-w-Java-Edition-protocol-Packets.md.
// The wiki tracks a moving/bleeding-edge protocol snapshot, so these MUST be re-verified
// against the actual client version this server is tested with (see plan Phase 3 checkpoint).
constexpr int32_t kHandshakeIntention = 0x00;

constexpr int32_t kStatusRequestId = 0x00;
constexpr int32_t kPingRequestId = 0x01;
constexpr int32_t kStatusResponseId = 0x00;
constexpr int32_t kPongResponseId = 0x01;

constexpr int32_t kLoginStartId = 0x00;
constexpr int32_t kLoginAcknowledgedId = 0x03;
constexpr int32_t kLoginSuccessId = 0x02;

constexpr int32_t kHandshakeIntentStatus = 1;
constexpr int32_t kHandshakeIntentLogin = 2;
constexpr int32_t kHandshakeIntentTransfer = 3;

// Configuration state packet IDs (clientbound and serverbound have separate ID spaces).
constexpr int32_t kConfigClientboundFinishConfiguration = 0x03;
constexpr int32_t kConfigClientboundRegistryData = 0x07;
constexpr int32_t kConfigClientboundKnownPacks = 0x0F;

constexpr int32_t kConfigServerboundKnownPacks = 0x07;
constexpr int32_t kConfigServerboundFinishConfigurationAck = 0x03;
} // namespace

ClientSession::ClientSession(std::shared_ptr<net::Connection> connection) : connection_(std::move(connection)) {}

void ClientSession::start() {
    auto self = shared_from_this();
    connection_->setPacketHandler([self](int32_t id, ByteReader& reader) { self->handlePacket(id, reader); });
    connection_->setDisconnectHandler([self]() { /* no per-session cleanup needed yet (no Play state) */ });
    connection_->start();
}

void ClientSession::handlePacket(int32_t packetId, ByteReader& reader) {
    switch (connection_->state()) {
    case ProtocolState::Handshaking: handleHandshake(packetId, reader); break;
    case ProtocolState::Status: handleStatus(packetId, reader); break;
    case ProtocolState::Login: handleLogin(packetId, reader); break;
    case ProtocolState::Configuration: handleConfiguration(packetId, reader); break;
    case ProtocolState::Play:
        // Play phase is not implemented yet.
        connection_->close();
        break;
    }
}

void ClientSession::handleHandshake(int32_t packetId, ByteReader& reader) {
    if (packetId != kHandshakeIntention) {
        connection_->close();
        return;
    }
    [[maybe_unused]] int32_t protocolVersion = reader.readVarInt();
    [[maybe_unused]] std::string serverAddress = reader.readString();
    [[maybe_unused]] uint16_t serverPort = reader.readUShort();
    int32_t intent = reader.readVarInt();

    if (intent == kHandshakeIntentStatus) {
        connection_->setState(ProtocolState::Status);
    } else if (intent == kHandshakeIntentLogin || intent == kHandshakeIntentTransfer) {
        connection_->setState(ProtocolState::Login);
    } else {
        connection_->close();
    }
}

void ClientSession::handleStatus(int32_t packetId, ByteReader& reader) {
    if (packetId == kStatusRequestId) {
        // Version/protocol per references/minecraft-wiki-w-Java-Edition-protocol-Packets.md line 1208
        // ("currently 777 in Minecraft 26.3") — the doc's documented "current" snapshot, not 1.21.4.
        static constexpr auto kStatusJson = R"({"version":{"name":"26.3","protocol":777},)"
                                             R"("players":{"max":20,"online":0},)"
                                             R"("description":{"text":"CS2310 minimal MC server"}})";
        ByteWriter body;
        body.writeString(kStatusJson);
        connection_->send(kStatusResponseId, body);
    } else if (packetId == kPingRequestId) {
        int64_t timestamp = reader.readLong();
        ByteWriter body;
        body.writeLong(timestamp);
        connection_->send(kPongResponseId, body);
    } else {
        connection_->close();
    }
}

void ClientSession::handleLogin(int32_t packetId, ByteReader& reader) {
    if (packetId == kLoginStartId) {
        playerName_ = reader.readString();
        [[maybe_unused]] auto clientSuppliedUuid = reader.readUuid();

        auto uuid = util::offlinePlayerUuid(playerName_);

        ByteWriter body;
        body.writeUuid(uuid);         // Game Profile: UUID
        body.writeString(playerName_); // Game Profile: Username
        body.writeVarInt(0);           // Game Profile: Properties (empty array)
        body.writeUuid(uuid);          // Session ID (reuse player UUID; unused downstream in this server)
        connection_->send(kLoginSuccessId, body);
    } else if (packetId == kLoginAcknowledgedId) {
        connection_->setState(ProtocolState::Configuration);
        enterConfiguration();
    } else {
        // Encryption/plugin-response packets are not supported (offline mode, no plugin channels).
        connection_->close();
    }
}

void ClientSession::enterConfiguration() { sendKnownPacks(); }

void ClientSession::sendKnownPacks() {
    // We claim to know no data packs, forcing the server to send full NBT for every
    // registry entry below rather than relying on the client already having them.
    ByteWriter body;
    body.writeVarInt(0); // Known Packs (empty array)
    connection_->send(kConfigClientboundKnownPacks, body);
}

void ClientSession::sendRegistryData() {
    for (auto const& registry : protocol::buildMinimalRegistries()) {
        ByteWriter body;
        body.writeString(registry.id);
        body.writeVarInt(static_cast<int32_t>(registry.entries.size()));
        for (auto const& entry : registry.entries) {
            body.writeString(entry.id);
            body.writeBool(true); // Prefixed Optional NBT: present
            std::string nbtBytes = protocol::toJavaNetworkNbt(entry.data);
            body.writeBytes(std::as_bytes(std::span<const char>(nbtBytes)));
        }
        connection_->send(kConfigClientboundRegistryData, body);
    }
}

void ClientSession::sendFinishConfiguration() {
    ByteWriter body;
    connection_->send(kConfigClientboundFinishConfiguration, body);
}

void ClientSession::handleConfiguration(int32_t packetId, ByteReader& reader) {
    if (packetId == kConfigServerboundKnownPacks) {
        // We don't care which packs the client claims to know; we always send full data.
        sendRegistryData();
        sendFinishConfiguration();
    } else if (packetId == kConfigServerboundFinishConfigurationAck) {
        connection_->setState(ProtocolState::Play);
        // Play-phase gameplay (Phase 4 onward) is not implemented yet.
        std::cerr << "[mcserver] player '" << playerName_
                  << "' reached Play state, which isn't implemented yet; closing connection.\n";
        connection_->close();
    } else {
        // Client Information / Plugin Message / Cookie Response / etc. — not needed yet, ignore.
        (void)reader;
    }
}

} // namespace mcserver::server
