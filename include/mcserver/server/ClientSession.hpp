#pragma once

#include "mcserver/net/Connection.hpp"
#include "mcserver/server/PlayerInventory.hpp"

#include <array>
#include <chrono>
#include <cstdint>
#include <exception>
#include <memory>
#include <limits>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace mcserver::server {

class World;

// Handles the packet-level conversation for a single connected client:
// Handshake -> (Status | Login -> Configuration -> Play).
class ClientSession : public std::enable_shared_from_this<ClientSession> {
public:
    ClientSession(std::shared_ptr<net::Connection> connection, std::shared_ptr<World> world,
                  std::string motd, int32_t viewDistance = 10);

    void start();

private:
    void handlePacket(int32_t packetId, net::ByteReader& reader);
    void handleHandshake(int32_t packetId, net::ByteReader& reader);
    void handleStatus(int32_t packetId, net::ByteReader& reader);
    void handleLogin(int32_t packetId, net::ByteReader& reader);
    void handleConfiguration(int32_t packetId, net::ByteReader& reader);
    void handlePlay(int32_t packetId, net::ByteReader& reader);

    void enterConfiguration();
    void sendKnownPacks();
    void sendRegistryData();
    void sendUpdateTags();
    void sendFinishConfiguration();
    void enterPlay();
    void sendPlayLogin();
    void sendPlayerAbilities();
    void sendInitialInventory();
    void sendInitialSpawn();
    void sendInitialChunks();
    void updateChunks(int32_t centerX, int32_t centerZ);
    void updateChunkCredit();
    void scheduleChunkBatch();
    void sendNextChunk();
    void failChunkStreaming(std::exception const& error);
    void handleMovement(double x, double y, double z, bool onGround);
    void sendPlayerPosition();
    void handleBlockPlacement(int hand, net::BlockPos const& target, int face);
    void sendBlockUpdate(net::BlockPos const& position, int32_t blockState);
    void handleBlockBreak(int x, int y, int z);
    void scheduleKeepAlive();
    void savePlayerProfile();
    void sendContainerContent();

    std::shared_ptr<net::Connection> connection_;
    std::shared_ptr<World> world_;
    asio::steady_timer keepAliveTimer_;
    asio::steady_timer chunkTimer_;
    std::string motd_;
    int32_t viewDistance_ = 10;
    std::string playerName_;
    std::array<std::byte, 16> playerUuid_{};
    bool hasPlayerUuid_ = false;
    bool hasEnteredPlay_ = false;
    PlayerInventory inventory_;
    PlayerProfile profile_;
    double positionX_ = 0.5;
    double positionY_ = 1.0;
    double positionZ_ = 0.5;
    float yaw_ = 0.0f;
    float pitch_ = 0.0f;
    bool onGround_ = true;
    std::array<int32_t, 9> hotbarItemIds_{};
    int32_t offhandItemId_ = 0;
    int16_t selectedHotbarSlot_ = 0;
    int32_t nextTeleportId_ = 0;
    int32_t pendingTeleportId_ = -1;
    int32_t inventoryStateId_ = 0;
    bool awaitingTeleportConfirmation_ = false;
    int32_t centerChunkX_ = std::numeric_limits<int32_t>::min();
    int32_t centerChunkZ_ = std::numeric_limits<int32_t>::min();
    std::set<std::pair<int32_t, int32_t>> sentChunks_;
    std::vector<std::pair<int32_t, int32_t>> pendingChunks_;
    size_t nextChunk_ = 0;
    float chunksPerTick_ = 1.0f;
    float chunkCredit_ = 1.0f;
    std::chrono::steady_clock::time_point lastChunkTick_;
    int32_t batchLimit_ = 0;
    int32_t batchCount_ = 0;
    bool sendingBatch_ = false;
    bool awaitingBatchAck_ = false;
    bool chunkTimerScheduled_ = false;
    bool disconnected_ = false;
};

} // namespace mcserver::server
