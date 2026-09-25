#pragma once

#include "mcserver/net/Connection.hpp"

#include <cstdint>
#include <memory>
#include <string>

namespace mcserver::server {

// Handles the packet-level conversation for a single connected client:
// Handshake -> (Status | Login -> Configuration -> Play).
class ClientSession : public std::enable_shared_from_this<ClientSession> {
public:
    explicit ClientSession(std::shared_ptr<net::Connection> connection);

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
    void sendInitialSpawn();
    void sendInitialChunks();
    void scheduleKeepAlive();

    std::shared_ptr<net::Connection> connection_;
    asio::steady_timer keepAliveTimer_;
    std::string playerName_;
    double positionX_ = 0.5;
    double positionY_ = 65.0;
    double positionZ_ = 0.5;
    float yaw_ = 0.0f;
    float pitch_ = 0.0f;
    bool onGround_ = false;
};

} // namespace mcserver::server
