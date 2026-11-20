#include "mcserver/server/ClientSession.hpp"
#include "mcserver/server/ChunkData.hpp"
#include "mcserver/protocol/Nbt.hpp"
#include "mcserver/protocol/Registries.hpp"
#include "mcserver/protocol/Tags.hpp"
#include "mcserver/server/World.hpp"
#include "mcserver/util/Md5.hpp"
#include "mcserver/util/Logger.hpp"

#include <iostream>
#include <bit>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <limits>
#include <span>

#include <nlohmann/json.hpp>

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
constexpr int32_t kPlayClientboundUnloadChunk = 0x26;
constexpr int32_t kPlayClientboundPlayerAbilities = 0x41;
constexpr int32_t kPlayClientboundSetContainerSlot = 0x14;
constexpr int32_t kPlayClientboundPlayerPosition = 0x49;
constexpr int32_t kPlayClientboundSetCenterChunk = 0x60;
constexpr int32_t kPlayClientboundChunkBatchFinished = 0x0B;
constexpr int32_t kPlayClientboundChunkBatchStart = 0x0C;
constexpr int32_t kPlayClientboundChunkData = 0x2E;
constexpr int32_t kPlayClientboundKeepAlive = 0x2D;
constexpr int32_t kPlayClientboundBlockChangedAck = 0x04;
constexpr int32_t kPlayClientboundBlockUpdate = 0x08;

constexpr int32_t kPlayServerboundConfirmTeleportation = 0x00;
constexpr int32_t kPlayServerboundKeepAlive = 0x1C;
constexpr int32_t kPlayServerboundSetPlayerPosition = 0x1E;
constexpr int32_t kPlayServerboundSetPlayerPositionAndRotation = 0x1F;
constexpr int32_t kPlayServerboundSetPlayerRotation = 0x20;
constexpr int32_t kPlayServerboundSetPlayerMovementFlags = 0x21;
constexpr int32_t kPlayServerboundPlayerLoaded = 0x2C;
constexpr int32_t kPlayServerboundPlayerAction = 0x29;
constexpr int32_t kPlayServerboundSetHeldItem = 0x36;
constexpr int32_t kPlayServerboundSetCreativeModeSlot = 0x39;
constexpr int32_t kPlayServerboundUseItemOn = 0x42;

constexpr int32_t kPlayerActionStartDigging = 0;
constexpr int32_t kPlayerActionFinishDigging = 2;
constexpr int32_t kAirBlockState = 0;
constexpr uint8_t kPlayerAbilitiesInvulnerable = 0x01;
constexpr uint8_t kPlayerAbilitiesAllowFlying = 0x04;
constexpr uint8_t kPlayerAbilitiesCreativeMode = 0x08;
constexpr int16_t kFirstHotbarSlot = 36;
constexpr int32_t kStoneItemId = 1;
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

ClientSession::ClientSession(std::shared_ptr<net::Connection> connection, std::shared_ptr<World> world,
                     std::string motd, int32_t viewDistance)
    : connection_(std::move(connection)),
      world_(std::move(world)),
    keepAliveTimer_(connection_->socket().get_executor()),
    motd_(std::move(motd)),
    viewDistance_(viewDistance) {}

void ClientSession::start() {
    auto self = shared_from_this();
    connection_->setPacketHandler([self](int32_t id, ByteReader& reader) { self->handlePacket(id, reader); });
    connection_->setDisconnectHandler([self]() {
        self->keepAliveTimer_.cancel();
        self->world_->removePlayer(self->connection_.get());
    });
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
        nlohmann::json status{{"version", {{"name", "26.3"}, {"protocol", 777}}},
                      {"players", {{"max", 20}, {"online", 0}}},
                      {"description", {{"text", motd_}}}};
        ByteWriter body;
        body.writeString(status.dump());
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

        asio::error_code endpointError;
        auto remote = connection_->socket().remote_endpoint(endpointError);
        if (!endpointError) {
            util::log(util::LogLevel::Info, "client connected from " + remote.address().to_string());
        }

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
    util::log(util::LogLevel::Debug, "received Play packet id " + std::to_string(packetId));
    switch (packetId) {
    case kPlayServerboundConfirmTeleportation: {
        int32_t teleportId = reader.readVarInt();
        (void)reader.readDouble();
        (void)reader.readDouble();
        (void)reader.readDouble();
        (void)reader.readFloat();
        (void)reader.readFloat();
        if (awaitingTeleportConfirmation_ && teleportId == pendingTeleportId_) {
            awaitingTeleportConfirmation_ = false;
        }
        break;
    }
    case kPlayServerboundKeepAlive:
        (void)reader.readLong();
        break;
    case kPlayServerboundSetPlayerPosition: {
        double x = reader.readDouble();
        double y = reader.readDouble();
        double z = reader.readDouble();
        bool onGround = reader.readBool();
        handleMovement(x, y, z, onGround);
        break;
    }
    case kPlayServerboundSetPlayerPositionAndRotation: {
        double x = reader.readDouble();
        double y = reader.readDouble();
        double z = reader.readDouble();
        float yaw = reader.readFloat();
        float pitch = reader.readFloat();
        bool onGround = reader.readBool();
        if (!std::isfinite(yaw) || !std::isfinite(pitch)) {
            connection_->close();
            break;
        }
        handleMovement(x, y, z, onGround);
        if (!awaitingTeleportConfirmation_) {
            yaw_ = yaw;
            pitch_ = pitch;
        }
        break;
    }
    case kPlayServerboundSetPlayerRotation: {
        float yaw = reader.readFloat();
        float pitch = reader.readFloat();
        bool onGround = reader.readBool();
        if (!std::isfinite(yaw) || !std::isfinite(pitch)) {
            connection_->close();
            break;
        }
        if (!awaitingTeleportConfirmation_) {
            yaw_ = yaw;
            pitch_ = pitch;
            onGround_ = onGround;
        }
        break;
    }
    case kPlayServerboundSetPlayerMovementFlags:
        if (!awaitingTeleportConfirmation_) {
            onGround_ = reader.readBool();
        } else {
            (void)reader.readBool();
        }
        break;
    case kPlayServerboundSetHeldItem: {
        int16_t slot = reader.readShort();
        if (slot < 0 || slot >= static_cast<int16_t>(hotbarItemIds_.size())) {
            connection_->close();
            break;
        }
        selectedHotbarSlot_ = slot;
        break;
    }
    case kPlayServerboundSetCreativeModeSlot: {
        int16_t slot = reader.readShort();
        int32_t count = reader.readVarInt();
        int32_t itemId = 0;
        if (count > 0) { itemId = reader.readVarInt(); }

        if (slot >= 36 && slot <= 44) {
            hotbarItemIds_[static_cast<size_t>(slot - 36)] = itemId;
        } else if (slot == 45) {
            offhandItemId_ = itemId;
        }
        break;
    }
    case kPlayServerboundPlayerLoaded:
        break;
    case kPlayServerboundPlayerAction: {
        int32_t action = reader.readVarInt();
        auto position = reader.readPosition();
        (void)reader.readByte(); // face
        int32_t sequence = reader.readVarInt();
        if (action == kPlayerActionStartDigging || action == kPlayerActionFinishDigging) {
            handleBlockBreak(position.x, position.y, position.z);
        }
        ByteWriter acknowledgement;
        acknowledgement.writeVarInt(sequence);
        connection_->send(kPlayClientboundBlockChangedAck, acknowledgement);
        break;
    }
    case kPlayServerboundUseItemOn: {
        int32_t hand = reader.readVarInt();
        auto target = reader.readPosition();
        int32_t face = reader.readVarInt();
        (void)reader.readFloat(); // cursor X
        (void)reader.readFloat(); // cursor Y
        (void)reader.readFloat(); // cursor Z
        (void)reader.readBool(); // inside block
        (void)reader.readBool(); // world border hit
        int32_t sequence = reader.readVarInt();
        handleBlockPlacement(hand, target, face);

        ByteWriter acknowledgement;
        acknowledgement.writeVarInt(sequence);
        connection_->send(kPlayClientboundBlockChangedAck, acknowledgement);
        break;
    }
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

void ClientSession::handleMovement(double x, double y, double z, bool onGround) {
    if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z)) {
        connection_->close();
        return;
    }
    if (awaitingTeleportConfirmation_) { return; }
    if (x < -33554432.0 || x >= 33554432.0 || z < -33554432.0 || z >= 33554432.0 || y < -64.0 || y >= 320.0) {
        sendPlayerPosition();
        return;
    }

    double deltaX = x - positionX_;
    double deltaY = y - positionY_;
    double deltaZ = z - positionZ_;
    constexpr double kMaximumMovementDistanceSquared = 10.0 * 10.0;
    if (deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ > kMaximumMovementDistanceSquared) {
        sendPlayerPosition();
        return;
    }

    positionX_ = x;
    positionY_ = y;
    positionZ_ = z;
    onGround_ = onGround;
    if (world_->javaWorld()) {
        int32_t chunkX = static_cast<int32_t>(std::floor(x / 16.0));
        int32_t chunkZ = static_cast<int32_t>(std::floor(z / 16.0));
        if (chunkX != centerChunkX_ || chunkZ != centerChunkZ_) { updateChunks(chunkX, chunkZ); }
    }
}

void ClientSession::sendPlayerPosition() {
    int32_t teleportId = nextTeleportId_;
    nextTeleportId_ =
        nextTeleportId_ == std::numeric_limits<int32_t>::max() ? 0 : nextTeleportId_ + 1;
    pendingTeleportId_ = teleportId;
    awaitingTeleportConfirmation_ = true;

    ByteWriter position;
    position.writeVarInt(teleportId);
    position.writeDouble(positionX_);
    position.writeDouble(positionY_);
    position.writeDouble(positionZ_);
    position.writeDouble(0.0);
    position.writeDouble(0.0);
    position.writeDouble(0.0);
    position.writeFloat(yaw_);
    position.writeFloat(pitch_);
    position.writeInt(0); // Absolute position and rotation
    connection_->send(kPlayClientboundPlayerPosition, position);
}

void ClientSession::sendBlockUpdate(net::BlockPos const& position, int32_t blockState) {
    ByteWriter update;
    update.writePosition(position);
    update.writeVarInt(blockState);
    connection_->send(kPlayClientboundBlockUpdate, update);
    for (auto const& player : world_->playersExcept(connection_.get())) {
        player->send(kPlayClientboundBlockUpdate, update);
    }
}

void ClientSession::handleBlockBreak(int x, int y, int z) {
    net::BlockPos position{.x = x, .y = y, .z = z};
    if (world_->setBlockToAir(position)) {
        sendBlockUpdate(position, kAirBlockState);
    } else if (auto* java = world_->javaWorld()) {
        if (auto state = java->blockStateAt(position)) { sendBlockUpdate(position, *state); }
    }
}

void ClientSession::handleBlockPlacement(int hand, net::BlockPos const& target, int face) {
    static constexpr std::array<net::BlockPos, 6> faceOffsets{{
        {0, -1, 0},
        {0, 1, 0},
        {0, 0, -1},
        {0, 0, 1},
        {-1, 0, 0},
        {1, 0, 0},
    }};
    if (hand < 0 || hand > 1 || face < 0 || face >= static_cast<int>(faceOffsets.size())) {
        return;
    }

    int32_t itemId = hand == 0 ? hotbarItemIds_[static_cast<size_t>(selectedHotbarSlot_)]
                               : offhandItemId_;
    auto blockState = world_->blockStateForItem(itemId);
    if (!blockState) { return; }

    auto const& offset = faceOffsets[static_cast<size_t>(face)];
    net::BlockPos position{
        .x = target.x + offset.x,
        .y = target.y + offset.y,
        .z = target.z + offset.z,
    };
    if (!world_->tryPlaceBlock(position, *blockState)) {
        if (auto* java = world_->javaWorld()) {
            if (auto state = java->blockStateAt(position)) { sendBlockUpdate(position, *state); }
        }
        return;
    }
    sendBlockUpdate(position, *blockState);
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
    world_->addPlayer(connection_);
    sendPlayLogin();
    sendPlayerAbilities();
    sendInitialInventory();
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
        body.writeVarInt(1);              // Game mode: Creative
        body.writeVarInt(0);              // Previous game mode: undefined
        body.writeBool(false);            // Is debug
        body.writeBool(world_->javaWorld() == nullptr); // Is flat
        body.writeBool(false);            // Has death location
        body.writeVarInt(0);              // Portal cooldown
        body.writeVarInt(63);             // Sea level
        body.writeBool(false);            // Offline mode
        body.writeBool(false);            // Does not enforce secure chat
        connection_->send(kPlayClientboundLogin, body);
    }

void ClientSession::sendPlayerAbilities() {
    ByteWriter body;
    body.writeUByte(kPlayerAbilitiesInvulnerable | kPlayerAbilitiesAllowFlying |
                    kPlayerAbilitiesCreativeMode);
    body.writeFloat(0.05f); // Flying speed
    body.writeFloat(0.1f);  // Field-of-view modifier
    connection_->send(kPlayClientboundPlayerAbilities, body);
}

void ClientSession::sendInitialInventory() {
    hotbarItemIds_[0] = kStoneItemId;

    ByteWriter slot;
    slot.writeVarInt(0); // Player inventory window
    slot.writeVarInt(0); // Initial state ID
    slot.writeShort(kFirstHotbarSlot);
    slot.writeVarInt(64); // Item count
    slot.writeVarInt(kStoneItemId);
    slot.writeVarInt(0); // Added components
    slot.writeVarInt(0); // Removed components
    connection_->send(kPlayClientboundSetContainerSlot, slot);
}

void ClientSession::sendInitialSpawn() {
        if (auto* java = world_->javaWorld()) {
            auto const& level = java->level();
            positionX_ = level.spawnX + 0.5;
            positionY_ = level.spawnY;
            positionZ_ = level.spawnZ + 0.5;
            yaw_ = level.spawnYaw;
            pitch_ = level.spawnPitch;
            ByteWriter event;
            event.writeUByte(13);
            event.writeFloat(0.0f);
            connection_->send(kPlayClientboundGameEvent, event);
            sendPlayerPosition();
            updateChunks(static_cast<int32_t>(std::floor(positionX_ / 16.0)),
                         static_cast<int32_t>(std::floor(positionZ_ / 16.0)));
            return;
        }
        ByteWriter center;
        center.writeVarInt(0);
        center.writeVarInt(0);
        connection_->send(kPlayClientboundSetCenterChunk, center);

        ByteWriter event;
        event.writeUByte(13);             // Start waiting for level chunks
        event.writeFloat(0.0f);
        connection_->send(kPlayClientboundGameEvent, event);

        sendPlayerPosition();
        sendInitialChunks();
}

    void ClientSession::sendInitialChunks() {
        ByteWriter start;
        connection_->send(kPlayClientboundChunkBatchStart, start);

        int32_t count = 0;
        for (int32_t chunkZ = -viewDistance_; chunkZ <= viewDistance_; ++chunkZ) {
            for (int32_t chunkX = -viewDistance_; chunkX <= viewDistance_; ++chunkX) {
                ByteWriter body;
                body.writeInt(chunkX);
                body.writeInt(chunkZ);

                body.writeVarInt(0); // heightmaps are optional; the client initializes them

                auto chunkData = makeFlatChunkData(*world_, chunkX, chunkZ);
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
                ++count;
            }
        }

        ByteWriter finished;
        finished.writeVarInt(count);
        connection_->send(kPlayClientboundChunkBatchFinished, finished);
    }

void ClientSession::updateChunks(int32_t centerX, int32_t centerZ) {
    ByteWriter center;
    center.writeVarInt(centerX);
    center.writeVarInt(centerZ);
    connection_->send(kPlayClientboundSetCenterChunk, center);
    centerChunkX_ = centerX;
    centerChunkZ_ = centerZ;
    for (auto iterator = sentChunks_.begin(); iterator != sentChunks_.end();) {
        auto [chunkX, chunkZ] = *iterator;
        if (std::abs(chunkX - centerX) <= viewDistance_ &&
            std::abs(chunkZ - centerZ) <= viewDistance_) { ++iterator; continue; }
        ByteWriter unload;
        unload.writeInt(chunkZ);
        unload.writeInt(chunkX);
        connection_->send(kPlayClientboundUnloadChunk, unload);
        iterator = sentChunks_.erase(iterator);
    }
    ByteWriter start;
    connection_->send(kPlayClientboundChunkBatchStart, start);
    int32_t count = 0;
    for (int32_t chunkZ = centerZ - viewDistance_; chunkZ <= centerZ + viewDistance_; ++chunkZ) {
        for (int32_t chunkX = centerX - viewDistance_; chunkX <= centerX + viewDistance_; ++chunkX) {
            auto chunk = world_->javaWorld()->chunk(chunkX, chunkZ);
            if (sentChunks_.contains({chunkX, chunkZ}) || !chunk) { continue; }
            ByteWriter body;
            body.writeInt(chunkX);
            body.writeInt(chunkZ);
            body.writeVarInt(0);
            auto data = makeFlatChunkData(*world_, chunkX, chunkZ);
            body.writeVarInt(static_cast<int32_t>(data.size()));
            body.writeBytes(data);
            body.writeVarInt(0);
            writeJavaChunkLight(body, chunk->data);
            connection_->send(kPlayClientboundChunkData, body);
            sentChunks_.insert({chunkX, chunkZ});
            ++count;
        }
    }
    ByteWriter finished;
    finished.writeVarInt(count);
    connection_->send(kPlayClientboundChunkBatchFinished, finished);
}

} // namespace mcserver::server
