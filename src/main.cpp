#include "mcserver/server/Server.hpp"
#include "mcserver/server/ServerProperties.hpp"
#include "mcserver/util/Logger.hpp"

#include <asio.hpp>

#include <cstdint>
#include <csignal>
#include <filesystem>
#include <cstdlib>
#include <string>

int main(int argc, char** argv) {
    if (char const* configuredLevel = std::getenv("MCSERVER_LOG_LEVEL")) {
        auto parsedLevel = mcserver::util::parseLogLevel(configuredLevel);
        if (parsedLevel) {
            mcserver::util::setLogLevel(*parsedLevel);
        } else {
            mcserver::util::log(mcserver::util::LogLevel::Warning,
                                "unrecognized MCSERVER_LOG_LEVEL; using info (valid: error, warning, info, debug)");
        }
    }

    try {
        if (argc > 1) { throw std::runtime_error("positional arguments are not supported; configure server.properties"); }
        auto properties = mcserver::server::loadServerProperties("server.properties");
        asio::io_context ioContext;
        mcserver::server::Server server(ioContext, properties.serverIp.empty() ? "0.0.0.0" : properties.serverIp,
                        properties.serverPort, properties.levelName, properties.motd,
                        properties.viewDistance);
        asio::signal_set shutdownSignals(ioContext, SIGINT, SIGTERM);
        shutdownSignals.async_wait([&ioContext](asio::error_code error, int) {
            if (!error) { ioContext.stop(); }
        });
        server.start();

        mcserver::util::log(mcserver::util::LogLevel::Info,
                            "listening on port " + std::to_string(properties.serverPort) + " (offline mode, no compression)");
        ioContext.run();
        return server.stop() ? 0 : 1;
    } catch (std::exception const& e) {
        mcserver::util::log(mcserver::util::LogLevel::Error, e.what());
        return 1;
    }
    return 0;
}
