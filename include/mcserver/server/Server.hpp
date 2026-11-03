#pragma once

#include <asio.hpp>

#include <cstdint>
#include <string>

namespace mcserver::server {

// Accepts incoming TCP connections and spawns a ClientSession for each one.
class Server {
public:
    Server(asio::io_context& ioContext, std::string bindAddress, uint16_t port);

    void start();

private:
    void doAccept();

    asio::io_context& ioContext_;
    asio::ip::tcp::acceptor acceptor_;
};

} // namespace mcserver::server
