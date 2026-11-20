#include "mcserver/server/WorldLock.hpp"

#include <catch2/catch_test_macros.hpp>

#include <atomic>
#include <chrono>
#include <fstream>

#ifndef _WIN32
#include <sys/wait.h>
#include <unistd.h>
#endif

TEST_CASE("World session lock excludes another process and releases on destruction", "[world-lock]") {
    static std::atomic<unsigned> next{0};
    auto directory = std::filesystem::temp_directory_path() /
        ("mcserver-lock-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) +
         "-" + std::to_string(next++));
    std::filesystem::create_directory(directory);
    struct Cleanup {
        std::filesystem::path directory;
        ~Cleanup() { std::error_code ignored; std::filesystem::remove_all(directory, ignored); }
    } cleanup{directory};
    {
        mcserver::server::WorldLock lock(directory);
        std::ifstream input(directory / "session.lock", std::ios::binary);
        REQUIRE(std::string(std::istreambuf_iterator<char>(input), {}) == "\xe2\x98\x83");
#ifndef _WIN32
        auto child = fork();
        REQUIRE(child >= 0);
        if (child == 0) {
            try { mcserver::server::WorldLock other(directory); _exit(1); }
            catch (...) { _exit(0); }
        }
        int status = 0;
        REQUIRE(waitpid(child, &status, 0) == child);
        REQUIRE(WIFEXITED(status));
        REQUIRE(WEXITSTATUS(status) == 0);
#endif
    }
    REQUIRE_NOTHROW(mcserver::server::WorldLock(directory));
}
