#pragma once

#include "mcserver/net/Connection.hpp"

#include <cstdint>
#include <memory>
#include <string>

namespace mcserver::server {

// Handles the packet-level conversation for a single connected client:
// Handshake -> (Status | Login -> Configuration -> Play). Play-phase gameplay
// logic is not implemented yet (see plan Phase 4 onward) — sessions are closed
// right after Configuration finishes until that work lands.
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

    void enterConfiguration();
    void sendKnownPacks();
    void sendRegistryData();
    void sendUpdateTags();
    void sendFinishConfiguration();

    std::shared_ptr<net::Connection> connection_;
    std::string playerName_;
};

} // namespace mcserver::server
