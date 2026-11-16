#include "mcserver/server/Server.hpp"
#include "mcserver/net/Connection.hpp"
#include "mcserver/server/ClientSession.hpp"
#include "mcserver/util/Logger.hpp"

#include <string>
#include <chrono>
#include <cstdlib>

namespace mcserver::server {

Server::Server(asio::io_context& ioContext, std::string bindAddress, uint16_t port,
               std::filesystem::path worldFile)
    : ioContext_(ioContext),
      acceptor_(ioContext, asio::ip::tcp::endpoint(asio::ip::make_address(bindAddress), port)),
      autosaveTimer_(ioContext_), storage_(std::move(worldFile)) {
    try {
        if (char const* directory = std::getenv("MCSERVER_WORLD_DIR"); directory && *directory) {
            world_->loadAnvil(directory);
            util::log(util::LogLevel::Info, "imported " + world_->worldName() + " (9 chunks, " + world_->identity() + ")");
        }
        bool loaded = storage_.load(*world_);
        util::log(util::LogLevel::Info,
                  std::string(loaded ? "loaded world from " : "new world; save path ") + storage_.path().string());
    } catch (std::exception const& error) {
        throw std::runtime_error("cannot load world '" + storage_.path().string() + "': " + error.what());
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
        storage_.save(*world_);
        world_->markSaved();
        util::log(util::LogLevel::Info, "saved world to " + storage_.path().string());
        return true;
    } catch (std::exception const& error) {
        util::log(util::LogLevel::Error, "cannot save world '" + storage_.path().string() + "': " + error.what());
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
            auto session = std::make_shared<ClientSession>(connection, world_);
            session->start();
        } else if (acceptor_.is_open()) {
            util::log(util::LogLevel::Warning, "accept failed: " + ec.message());
        }
        if (acceptor_.is_open()) { doAccept(); }
    });
}

} // namespace mcserver::server
