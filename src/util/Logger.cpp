#include "mcserver/util/Logger.hpp"

#include <atomic>
#include <iostream>
#include <mutex>
#include <string_view>

namespace mcserver::util {

namespace {

std::atomic<LogLevel> minimumLogLevel{LogLevel::Info};
std::mutex outputMutex;

std::string_view levelName(LogLevel level) noexcept {
    switch (level) {
    case LogLevel::Error: return "ERROR";
    case LogLevel::Warning: return "WARNING";
    case LogLevel::Info: return "INFO";
    case LogLevel::Debug: return "DEBUG";
    }
    return "UNKNOWN";
}

} // namespace

std::optional<LogLevel> parseLogLevel(std::string_view value) noexcept {
    if (value == "error") { return LogLevel::Error; }
    if (value == "warning") { return LogLevel::Warning; }
    if (value == "info") { return LogLevel::Info; }
    if (value == "debug") { return LogLevel::Debug; }
    return std::nullopt;
}

void setLogLevel(LogLevel level) noexcept { minimumLogLevel.store(level, std::memory_order_relaxed); }

void log(LogLevel level, std::string_view message) {
    if (static_cast<int>(level) > static_cast<int>(minimumLogLevel.load(std::memory_order_relaxed))) {
        return;
    }

    std::lock_guard lock(outputMutex);
    std::cerr << '[' << levelName(level) << "] [mcserver] " << message << '\n';
}

} // namespace mcserver::util
