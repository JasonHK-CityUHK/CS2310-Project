#pragma once

#include <asio.hpp>

#include <cstdint>
#include <string>
#include <memory>
#include <vector>

#include "mcserver/server/World.hpp"

namespace mcserver::server {

class ClientSession;

// Accepts incoming TCP connections and spawns a ClientSession for each one.
class Server {
public:
        Server(asio::io_context& ioContext, std::string bindAddress, uint16_t port,
            std::filesystem::path worldDirectory = "world",
            std::string motd = "CS2310 minimal MC server", int32_t viewDistance = 10);

    void start();
    bool stop();

private:
    void doAccept();
    void scheduleAutosave();
    bool saveWorld();

    asio::io_context& ioContext_;
    asio::ip::tcp::acceptor acceptor_;
    asio::steady_timer autosaveTimer_;
    std::string motd_;
    int32_t viewDistance_ = 10;
    std::shared_ptr<World> world_;
};

} // namespace mcserver::server
