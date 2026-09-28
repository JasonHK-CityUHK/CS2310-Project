#pragma once

#include <optional>
#include <string_view>

namespace mcserver::util {

enum class LogLevel {
    Error,
    Warning,
    Info,
    Debug,
};

[[nodiscard]] std::optional<LogLevel> parseLogLevel(std::string_view value) noexcept;
void setLogLevel(LogLevel level) noexcept;
void log(LogLevel level, std::string_view message);

} // namespace mcserver::util
