#include "mcserver/util/Logger.hpp"

#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <sstream>
#include <string>

TEST_CASE("log levels parse by name") {
    using mcserver::util::LogLevel;

    REQUIRE(mcserver::util::parseLogLevel("error") == LogLevel::Error);
    REQUIRE(mcserver::util::parseLogLevel("warning") == LogLevel::Warning);
    REQUIRE(mcserver::util::parseLogLevel("info") == LogLevel::Info);
    REQUIRE(mcserver::util::parseLogLevel("debug") == LogLevel::Debug);
    REQUIRE_FALSE(mcserver::util::parseLogLevel("verbose"));
}

TEST_CASE("logger filters messages below the configured threshold") {
    using mcserver::util::LogLevel;

    std::ostringstream captured;
    auto* previousBuffer = std::cerr.rdbuf(captured.rdbuf());
    mcserver::util::setLogLevel(LogLevel::Warning);
    mcserver::util::log(LogLevel::Debug, "hidden debug");
    mcserver::util::log(LogLevel::Info, "hidden info");
    mcserver::util::log(LogLevel::Warning, "visible warning");
    mcserver::util::log(LogLevel::Error, "visible error");
    std::cerr.rdbuf(previousBuffer);
    mcserver::util::setLogLevel(LogLevel::Info);

    auto output = captured.str();
    REQUIRE(output.find("visible warning") != std::string::npos);
    REQUIRE(output.find("visible error") != std::string::npos);
    REQUIRE(output.find("hidden debug") == std::string::npos);
    REQUIRE(output.find("hidden info") == std::string::npos);
}
