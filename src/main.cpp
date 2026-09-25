#include "mcserver/server/Server.hpp"

#include <asio.hpp>

#include <cstdint>
#include <iostream>

int main(int argc, char** argv) {
    uint16_t port = 25565;
    if (argc > 1) { port = static_cast<uint16_t>(std::stoi(argv[1])); }

    try {
        asio::io_context ioContext;
        mcserver::server::Server server(ioContext, "0.0.0.0", port);
        server.start();

        std::cout << "[mcserver] listening on port " << port << " (offline mode, no compression)\n";
        ioContext.run();
    } catch (std::exception const& e) {
        std::cerr << "[mcserver] fatal error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
