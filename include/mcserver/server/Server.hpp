#pragma once

#include <asio.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace mcserver::server {

class World;

// Accepts incoming TCP connections and spawns a ClientSession for each one.
class Server {
public:
    Server(asio::io_context& ioContext, std::string bindAddress, uint16_t port);

    void start();

private:
    void doAccept();

    asio::io_context& ioContext_;
    asio::ip::tcp::acceptor acceptor_;
    std::shared_ptr<World> world_;
};

} // namespace mcserver::server
