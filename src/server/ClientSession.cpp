#include "mcserver/server/ClientSession.hpp"
#include "mcserver/protocol/Nbt.hpp"
#include "mcserver/protocol/Registries.hpp"
#include "mcserver/protocol/Tags.hpp"
#include "mcserver/util/Md5.hpp"

#include <iostream>
#include <bit>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <span>
#include <vector>

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
constexpr int32_t kConfigClientboundUpdateTags = 0x0E;
constexpr int32_t kConfigClientboundKnownPacks = 0x0F;

constexpr int32_t kConfigServerboundKnownPacks = 0x07;
constexpr int32_t kConfigServerboundFinishConfigurationAck = 0x03;

// Play clientbound packet IDs for protocol 777 / Minecraft 26.3.
constexpr int32_t kPlayClientboundLogin = 0x32;
constexpr int32_t kPlayClientboundGameEvent = 0x27;
constexpr int32_t kPlayClientboundPlayerPosition = 0x49;
constexpr int32_t kPlayClientboundSetCenterChunk = 0x60;
constexpr int32_t kPlayClientboundChunkBatchFinished = 0x0B;
constexpr int32_t kPlayClientboundChunkBatchStart = 0x0C;
constexpr int32_t kPlayClientboundChunkData = 0x2E;
constexpr int32_t kPlayClientboundKeepAlive = 0x2D;

constexpr int32_t kPlayServerboundConfirmTeleportation = 0x00;
constexpr int32_t kPlayServerboundKeepAlive = 0x1C;
constexpr int32_t kPlayServerboundSetPlayerPosition = 0x1E;
constexpr int32_t kPlayServerboundSetPlayerPositionAndRotation = 0x1F;
constexpr int32_t kPlayServerboundSetPlayerRotation = 0x20;
constexpr int32_t kPlayServerboundSetPlayerMovementFlags = 0x21;
constexpr int32_t kPlayServerboundPlayerLoaded = 0x2C;
} // namespace

void writeBitSet(net::ByteWriter& writer, uint64_t bits) {
    size_t byteCount = bits == 0 ? 0 : (64 - std::countl_zero(bits) + 7) / 8;
    writer.writeVarInt(static_cast<int32_t>(byteCount));
    for (size_t index = 0; index < byteCount; ++index) {
        writer.writeUByte(static_cast<uint8_t>(bits >> (index * 8)));
    }
}

void writeFullLightArray(net::ByteWriter& writer) {
    writer.writeVarInt(2048);
    for (int index = 0; index < 2048; ++index) { writer.writeUByte(0xFF); }
}

void writePalettedContainer(net::ByteWriter& writer, bool ground) {
    writer.writeUByte(ground ? 4 : 0);
    if (ground) {
        writer.writeVarInt(2); // air and stone local palette
        writer.writeVarInt(0);
        writer.writeVarInt(1); // global block state ID: stone
        std::vector<uint64_t> data(256, 0);
        for (int index = 0; index < 256; ++index) {
            size_t bit = static_cast<size_t>(index) * 4;
            data[bit / 64] |= uint64_t{1} << (bit % 64);
        }
        for (uint64_t word : data) { writer.writeLong(static_cast<int64_t>(word)); }
    } else {
        writer.writeVarInt(0); // single-valued air palette
    }
}

std::vector<std::byte> flatChunkData() {
    net::ByteWriter data;
    for (int section = 0; section < 24; ++section) {
        bool ground = section == 4;
        data.writeShort(ground ? 256 : 0);
        data.writeShort(0); // fluid count
        writePalettedContainer(data, ground);
        data.writeUByte(0); // single-valued biome palette
        data.writeVarInt(41); // plains biome registry ID
    }
    return data.take();
}

ClientSession::ClientSession(std::shared_ptr<net::Connection> connection)
    : connection_(std::move(connection)), keepAliveTimer_(connection_->socket().get_executor()) {}

void ClientSession::start() {
    auto self = shared_from_this();
    connection_->setPacketHandler([self](int32_t id, ByteReader& reader) { self->handlePacket(id, reader); });
    connection_->setDisconnectHandler([self]() { self->keepAliveTimer_.cancel(); });
    connection_->start();
}

void ClientSession::handlePacket(int32_t packetId, ByteReader& reader) {
    switch (connection_->state()) {
    case ProtocolState::Handshaking: handleHandshake(packetId, reader); break;
    case ProtocolState::Status: handleStatus(packetId, reader); break;
    case ProtocolState::Login: handleLogin(packetId, reader); break;
    case ProtocolState::Configuration: handleConfiguration(packetId, reader); break;
    case ProtocolState::Play: handlePlay(packetId, reader); break;
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

void ClientSession::sendUpdateTags() {
    ByteWriter body;
    auto taggedRegistries = protocol::buildMinimalTags();
    body.writeVarInt(static_cast<int32_t>(taggedRegistries.size()));
    for (auto const& registry : taggedRegistries) {
        body.writeString(registry.registryId);
        body.writeVarInt(static_cast<int32_t>(registry.tags.size()));
        for (auto const& tag : registry.tags) {
            body.writeString(tag.name);
            body.writeVarInt(static_cast<int32_t>(tag.entries.size()));
            for (int32_t entryId : tag.entries) { body.writeVarInt(entryId); }
        }
    }
    connection_->send(kConfigClientboundUpdateTags, body);
}

void ClientSession::sendFinishConfiguration() {
    ByteWriter body;
    connection_->send(kConfigClientboundFinishConfiguration, body);
}

void ClientSession::handleConfiguration(int32_t packetId, ByteReader& reader) {
    if (packetId == kConfigServerboundKnownPacks) {
        // We don't care which packs the client claims to know; we always send full data.
        sendRegistryData();
        sendUpdateTags();
        sendFinishConfiguration();
    } else if (packetId == kConfigServerboundFinishConfigurationAck) {
        connection_->setState(ProtocolState::Play);
        enterPlay();
    } else {
        // Client Information / Plugin Message / Cookie Response / etc. — not needed yet, ignore.
        (void)reader;
    }
}

void ClientSession::handlePlay(int32_t packetId, ByteReader& reader) {
    switch (packetId) {
    case kPlayServerboundConfirmTeleportation:
        (void)reader.readVarInt();
        break;
    case kPlayServerboundKeepAlive:
        (void)reader.readLong();
        break;
    case kPlayServerboundSetPlayerPosition:
        positionX_ = reader.readDouble();
        positionY_ = reader.readDouble();
        positionZ_ = reader.readDouble();
        onGround_ = reader.readBool();
        break;
    case kPlayServerboundSetPlayerPositionAndRotation:
        positionX_ = reader.readDouble();
        positionY_ = reader.readDouble();
        positionZ_ = reader.readDouble();
        yaw_ = reader.readFloat();
        pitch_ = reader.readFloat();
        onGround_ = reader.readBool();
        break;
    case kPlayServerboundSetPlayerRotation:
        yaw_ = reader.readFloat();
        pitch_ = reader.readFloat();
        onGround_ = reader.readBool();
        break;
    case kPlayServerboundSetPlayerMovementFlags:
        onGround_ = reader.readBool();
        break;
    case kPlayServerboundPlayerLoaded:
        break;
    default:
        // Other Play packets are intentionally ignored until their gameplay
        // state is implemented.
        (void)reader;
        break;
    }

    if (!std::isfinite(positionX_) || !std::isfinite(positionY_) || !std::isfinite(positionZ_) ||
        !std::isfinite(yaw_) || !std::isfinite(pitch_)) {
        connection_->close();
    }
}

void ClientSession::scheduleKeepAlive() {
    auto self = shared_from_this();
    keepAliveTimer_.expires_after(std::chrono::seconds(10));
    keepAliveTimer_.async_wait([self](asio::error_code error) {
        if (error || self->connection_->state() != ProtocolState::Play) { return; }

        ByteWriter body;
        auto now = std::chrono::steady_clock::now().time_since_epoch();
        body.writeLong(std::chrono::duration_cast<std::chrono::milliseconds>(now).count());
        self->connection_->send(kPlayClientboundKeepAlive, body);
        self->scheduleKeepAlive();
    });
}

void ClientSession::enterPlay() {
    sendPlayLogin();
    sendInitialSpawn();
    scheduleKeepAlive();
}

void ClientSession::sendPlayLogin() {
        ByteWriter body;
        body.writeInt(1);                 // Entity ID
        body.writeBool(false);            // Is hardcore
        body.writeVarInt(1);              // Dimension names array
        body.writeString("minecraft:overworld");
        body.writeVarInt(20);             // Max players (ignored)
        body.writeVarInt(8);              // View distance
        body.writeVarInt(8);              // Simulation distance
        body.writeBool(false);             // Reduced debug info
        body.writeBool(true);              // Enable respawn screen
        body.writeBool(false);            // Do limited crafting
        body.writeVarInt(0);              // Dimension type: sorted dimension_type ID
        body.writeString("minecraft:overworld");
        body.writeLong(0);                // Hashed seed
        body.writeVarInt(1);              // Creative
        body.writeVarInt(0);              // Previous game mode: undefined
        body.writeBool(false);            // Is debug
        body.writeBool(true);             // Is flat
        body.writeBool(false);            // Has death location
        body.writeVarInt(0);              // Portal cooldown
        body.writeVarInt(63);             // Sea level
        body.writeBool(false);            // Offline mode
        body.writeBool(false);            // Does not enforce secure chat
        connection_->send(kPlayClientboundLogin, body);
    }

void ClientSession::sendInitialSpawn() {
        ByteWriter center;
        center.writeVarInt(0);
        center.writeVarInt(0);
        connection_->send(kPlayClientboundSetCenterChunk, center);

        ByteWriter event;
        event.writeUByte(13);             // Start waiting for level chunks
        event.writeFloat(0.0f);
        connection_->send(kPlayClientboundGameEvent, event);

        ByteWriter position;
        position.writeVarInt(0);           // Teleport ID
        position.writeDouble(0.5);
        position.writeDouble(65.0);
        position.writeDouble(0.5);
        position.writeDouble(0.0);
        position.writeDouble(0.0);
        position.writeDouble(0.0);
        position.writeFloat(0.0f);
        position.writeFloat(0.0f);
        position.writeInt(0);              // Absolute position and rotation
        connection_->send(kPlayClientboundPlayerPosition, position);
        sendInitialChunks();
}

    void ClientSession::sendInitialChunks() {
        ByteWriter start;
        connection_->send(kPlayClientboundChunkBatchStart, start);

        for (int32_t chunkZ = -1; chunkZ <= 1; ++chunkZ) {
            for (int32_t chunkX = -1; chunkX <= 1; ++chunkX) {
                ByteWriter body;
                body.writeInt(chunkX);
                body.writeInt(chunkZ);

                body.writeVarInt(0); // heightmaps are optional; the client initializes them

                auto chunkData = flatChunkData();
                body.writeVarInt(static_cast<int32_t>(chunkData.size()));
                body.writeBytes(chunkData);
                body.writeVarInt(0); // Block entities

                constexpr uint64_t fullLightMask = (uint64_t{1} << 26) - 1;
                writeBitSet(body, fullLightMask); // Sky light mask
                writeBitSet(body, fullLightMask); // Block light mask
                writeBitSet(body, 0); // Empty sky light mask
                writeBitSet(body, 0); // Empty block light mask
                body.writeVarInt(26); // Sky light arrays
                for (int index = 0; index < 26; ++index) { writeFullLightArray(body); }
                body.writeVarInt(26); // Block light arrays
                for (int index = 0; index < 26; ++index) { writeFullLightArray(body); }
                connection_->send(kPlayClientboundChunkData, body);
            }
        }

        ByteWriter finished;
        finished.writeVarInt(9);
        connection_->send(kPlayClientboundChunkBatchFinished, finished);
    }

} // namespace mcserver::server
