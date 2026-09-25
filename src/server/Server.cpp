#include "mcserver/server/Server.hpp"
#include "mcserver/net/Connection.hpp"
#include "mcserver/server/ClientSession.hpp"

#include <iostream>

namespace mcserver::server {

Server::Server(asio::io_context& ioContext, std::string bindAddress, uint16_t port)
    : ioContext_(ioContext),
      acceptor_(ioContext, asio::ip::tcp::endpoint(asio::ip::make_address(bindAddress), port)) {}

void Server::start() { doAccept(); }

void Server::doAccept() {
    acceptor_.async_accept([this](asio::error_code ec, asio::ip::tcp::socket socket) {
        if (!ec) {
            socket.set_option(asio::ip::tcp::no_delay(true));
            auto connection = std::make_shared<net::Connection>(std::move(socket));
            auto session = std::make_shared<ClientSession>(connection);
            session->start();
        } else {
            std::cerr << "[mcserver] accept error: " << ec.message() << "\n";
        }
        doAccept();
    });
}

} // namespace mcserver::server
