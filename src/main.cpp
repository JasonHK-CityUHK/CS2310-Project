#include "mcserver/server/Server.hpp"
#include "mcserver/util/Logger.hpp"

#include <asio.hpp>

#include <cstdint>
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

    uint16_t port = 25565;
    if (argc > 1) { port = static_cast<uint16_t>(std::stoi(argv[1])); }

    try {
        asio::io_context ioContext;
        mcserver::server::Server server(ioContext, "0.0.0.0", port);
        server.start();

        mcserver::util::log(mcserver::util::LogLevel::Info,
                            "listening on port " + std::to_string(port) + " (offline mode, no compression)");
        ioContext.run();
    } catch (std::exception const& e) {
        mcserver::util::log(mcserver::util::LogLevel::Error, e.what());
        return 1;
    }
    return 0;
}
