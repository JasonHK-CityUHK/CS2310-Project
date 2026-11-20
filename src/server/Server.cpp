#include "mcserver/server/Server.hpp"
#include "mcserver/net/Connection.hpp"
#include "mcserver/server/ClientSession.hpp"
#include "mcserver/util/Logger.hpp"

#include <string>
#include <chrono>

namespace mcserver::server {

Server::Server(asio::io_context& ioContext, std::string bindAddress, uint16_t port,
           std::filesystem::path worldDirectory, std::string motd, int32_t viewDistance)
    : ioContext_(ioContext),
      acceptor_(ioContext, asio::ip::tcp::endpoint(asio::ip::make_address(bindAddress), port)),
    autosaveTimer_(ioContext_), motd_(std::move(motd)), viewDistance_(viewDistance) {
    try {
                world_ = std::make_shared<World>(worldDirectory);
                util::log(util::LogLevel::Info, "loaded world from " + worldDirectory.string());
    } catch (std::exception const& error) {
                throw std::runtime_error("cannot load world '" + worldDirectory.string() + "': " + error.what());
    }
}

void Server::start() {
    doAccept();
    scheduleAutosave();
}

bool Server::stop() {
    asio::error_code ignored;
    acceptor_.close(ignored);
    autosaveTimer_.cancel();
    return saveWorld();
}

bool Server::saveWorld() {
    if (!world_->dirty()) { return true; }
    try {
        world_->saveJavaWorld();
        util::log(util::LogLevel::Info, "saved world");
        return true;
    } catch (std::exception const& error) {
        util::log(util::LogLevel::Error, std::string("cannot save world: ") + error.what());
        return false;
    }
}

void Server::scheduleAutosave() {
    autosaveTimer_.expires_after(std::chrono::seconds(5));
    autosaveTimer_.async_wait([this](asio::error_code error) {
        if (error) { return; }
        saveWorld(); // A failed save stays dirty and is retried on the next tick.
        scheduleAutosave();
    });
}

void Server::doAccept() {
    acceptor_.async_accept([this](asio::error_code ec, asio::ip::tcp::socket socket) {
        if (!ec) {
            socket.set_option(asio::ip::tcp::no_delay(true));
            auto connection = std::make_shared<net::Connection>(std::move(socket));
            auto session = std::make_shared<ClientSession>(connection, world_, motd_, viewDistance_);
            session->start();
        } else if (acceptor_.is_open()) {
            util::log(util::LogLevel::Warning, "accept failed: " + ec.message());
        }
        if (acceptor_.is_open()) { doAccept(); }
    });
}

} // namespace mcserver::server
