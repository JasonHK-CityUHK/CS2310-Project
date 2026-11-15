#pragma once

#include "mcserver/net/Connection.hpp"

#include <array>
#include <cstdint>
#include <memory>
#include <string>

namespace mcserver::server {

class World;

// Handles the packet-level conversation for a single connected client:
// Handshake -> (Status | Login -> Configuration -> Play).
class ClientSession : public std::enable_shared_from_this<ClientSession> {
public:
    ClientSession(std::shared_ptr<net::Connection> connection, std::shared_ptr<World> world);

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
    void handleMovement(double x, double y, double z, bool onGround);
    void sendPlayerPosition();
    void handleBlockPlacement(int hand, net::BlockPos const& target, int face);
    void sendBlockUpdate(net::BlockPos const& position, int32_t blockState);
    void handleBlockBreak(int x, int y, int z);
    void scheduleKeepAlive();

    std::shared_ptr<net::Connection> connection_;
    std::shared_ptr<World> world_;
    asio::steady_timer keepAliveTimer_;
    std::string playerName_;
    double positionX_ = 0.5;
    double positionY_ = 65.0;
    double positionZ_ = 0.5;
    float yaw_ = 0.0f;
    float pitch_ = 0.0f;
    bool onGround_ = false;
    std::array<int32_t, 9> hotbarItemIds_{};
    int32_t offhandItemId_ = 0;
    int16_t selectedHotbarSlot_ = 0;
    int32_t nextTeleportId_ = 0;
    int32_t pendingTeleportId_ = -1;
    bool awaitingTeleportConfirmation_ = false;
};

} // namespace mcserver::server
