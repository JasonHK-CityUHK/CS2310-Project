#pragma once

#include <asio.hpp>

#include <cstdint>
#include <string>
#include <memory>
#include <vector>

#include "mcserver/server/World.hpp"
#include "mcserver/server/WorldStorage.hpp"

namespace mcserver::server {

class ClientSession;

// Accepts incoming TCP connections and spawns a ClientSession for each one.
class Server {
public:
    Server(asio::io_context& ioContext, std::string bindAddress, uint16_t port,
           std::filesystem::path worldFile = "world/flat-world.json");

    void start();
    bool stop();

private:
    void doAccept();
    void scheduleAutosave();
    bool saveWorld();

    asio::io_context& ioContext_;
    asio::ip::tcp::acceptor acceptor_;
    asio::steady_timer autosaveTimer_;
    WorldStorage storage_;
    std::shared_ptr<World> world_ = std::make_shared<World>();
};

} // namespace mcserver::server
