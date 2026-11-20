#include "mcserver/server/ServerProperties.hpp"

#include <asio.hpp>

#include <charconv>
#include <fstream>
#include <stdexcept>
#include <string_view>
#include <unordered_map>

namespace mcserver::server {
namespace {

bool isSpace(char value) { return value == ' ' || value == '\t' || value == '\f'; }

void appendUtf8(std::string& output, uint32_t codepoint) {
    if (codepoint <= 0x7f) {
        output.push_back(static_cast<char>(codepoint));
    } else if (codepoint <= 0x7ff) {
        output.push_back(static_cast<char>(0xc0 | (codepoint >> 6)));
        output.push_back(static_cast<char>(0x80 | (codepoint & 0x3f)));
    } else if (codepoint <= 0xffff) {
        output.push_back(static_cast<char>(0xe0 | (codepoint >> 12)));
        output.push_back(static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
        output.push_back(static_cast<char>(0x80 | (codepoint & 0x3f)));
    } else {
        output.push_back(static_cast<char>(0xf0 | (codepoint >> 18)));
        output.push_back(static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
        output.push_back(static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
        output.push_back(static_cast<char>(0x80 | (codepoint & 0x3f)));
    }
}

uint32_t readUnicode(std::string_view text, size_t& index) {
    if (index + 4 > text.size()) { throw std::runtime_error("invalid Unicode escape in server.properties"); }
    uint32_t result = 0;
    for (int digit = 0; digit < 4; ++digit) {
        char value = text[index++];
        result <<= 4;
        if (value >= '0' && value <= '9') { result += value - '0'; }
        else if (value >= 'a' && value <= 'f') { result += value - 'a' + 10; }
        else if (value >= 'A' && value <= 'F') { result += value - 'A' + 10; }
        else { throw std::runtime_error("invalid Unicode escape in server.properties"); }
    }
    return result;
}

std::string unescape(std::string_view text) {
    std::string result;
    for (size_t index = 0; index < text.size(); ++index) {
        char value = text[index];
        if (value != '\\') { result.push_back(value); continue; }
        if (++index == text.size()) { break; }
        value = text[index];
        if (value == 't') { result.push_back('\t'); }
        else if (value == 'n') { result.push_back('\n'); }
        else if (value == 'r') { result.push_back('\r'); }
        else if (value == 'f') { result.push_back('\f'); }
        else if (value == 'u') {
            ++index;
            uint32_t codepoint = readUnicode(text, index);
            if (codepoint >= 0xd800 && codepoint <= 0xdbff) {
                if (index + 2 > text.size() || text[index] != '\\' || text[index + 1] != 'u') {
                    throw std::runtime_error("unpaired Unicode surrogate in server.properties");
                }
                index += 2;
                uint32_t low = readUnicode(text, index);
                if (low < 0xdc00 || low > 0xdfff) {
                    throw std::runtime_error("unpaired Unicode surrogate in server.properties");
                }
                codepoint = 0x10000 + ((codepoint - 0xd800) << 10) + (low - 0xdc00);
            } else if (codepoint >= 0xdc00 && codepoint <= 0xdfff) {
                throw std::runtime_error("unpaired Unicode surrogate in server.properties");
            }
            appendUtf8(result, codepoint);
            --index;
        } else { result.push_back(value); }
    }
    return result;
}

void readProperty(std::string const& line, std::unordered_map<std::string, std::string>& values) {
    size_t start = line.find_first_not_of(" \t\f");
    if (start == std::string::npos || line[start] == '#' || line[start] == '!') { return; }
    size_t end = start;
    bool escaped = false;
    while (end < line.size()) {
        char value = line[end];
        if (!escaped && (value == '=' || value == ':' || isSpace(value))) { break; }
        if (value == '\\') { escaped = !escaped; }
        else { escaped = false; }
        ++end;
    }
    size_t valueStart = end;
    while (valueStart < line.size() && isSpace(line[valueStart])) { ++valueStart; }
    if (valueStart < line.size() && (line[valueStart] == '=' || line[valueStart] == ':')) { ++valueStart; }
    while (valueStart < line.size() && isSpace(line[valueStart])) { ++valueStart; }
    std::string key = unescape(std::string_view(line).substr(start, end - start));
    if (key == "server-ip" || key == "server-port" || key == "view-distance" ||
        key == "motd" || key == "level-name") {
        values[std::move(key)] = unescape(std::string_view(line).substr(valueStart));
    }
}

} // namespace

ServerProperties parseServerProperties(std::istream& input) {
    std::unordered_map<std::string, std::string> values;
    std::string line;
    std::string logicalLine;
    bool continued = false;
    while (std::getline(input, line)) {
        if (!line.empty() && line.back() == '\r') { line.pop_back(); }
        if (continued) {
            size_t start = line.find_first_not_of(" \t\f");
            logicalLine += start == std::string::npos ? "" : line.substr(start);
        } else {
            logicalLine = line;
            size_t start = logicalLine.find_first_not_of(" \t\f");
            if (start == std::string::npos || logicalLine[start] == '#' || logicalLine[start] == '!') { continue; }
        }
        size_t slashes = 0;
        while (slashes < logicalLine.size() && logicalLine[logicalLine.size() - slashes - 1] == '\\') { ++slashes; }
        continued = slashes % 2 != 0;
        if (continued) { logicalLine.pop_back(); }
        else { readProperty(logicalLine, values); }
    }
    if (input.bad()) { throw std::runtime_error("cannot read server.properties"); }
    if (continued) { readProperty(logicalLine, values); }

    ServerProperties result;
    if (values.contains("server-ip")) {
        result.serverIp = values.at("server-ip");
        if (!result.serverIp.empty()) {
            asio::error_code error;
            asio::ip::make_address(result.serverIp, error);
            if (error) { throw std::runtime_error("invalid server-ip in server.properties"); }
        }
    }
    if (values.contains("server-port")) {
        auto const& value = values.at("server-port");
        unsigned port = 0;
        auto [end, error] = std::from_chars(value.data(), value.data() + value.size(), port);
        if (error != std::errc{} || end != value.data() + value.size() || port == 0 || port > 65535) {
            throw std::runtime_error("invalid server-port in server.properties");
        }
        result.serverPort = static_cast<uint16_t>(port);
    }
    if (values.contains("view-distance")) {
        auto const& value = values.at("view-distance");
        int32_t viewDistance = 0;
        auto [end, error] = std::from_chars(value.data(), value.data() + value.size(), viewDistance);
        if (error != std::errc{} || end != value.data() + value.size() ||
            viewDistance < 3 || viewDistance > 32) {
            throw std::runtime_error("invalid view-distance in server.properties");
        }
        result.viewDistance = viewDistance;
    }
    if (values.contains("motd")) { result.motd = values.at("motd"); }
    if (values.contains("level-name")) {
        if (values.at("level-name").empty() || values.at("level-name").find('\0') != std::string::npos) {
            throw std::runtime_error("invalid level-name in server.properties");
        }
        result.levelName = values.at("level-name");
    }
    return result;
}

ServerProperties loadServerProperties(std::filesystem::path const& path) {
    if (!std::filesystem::exists(path)) { return {}; }
    std::ifstream input(path, std::ios::binary);
    if (!input) { throw std::runtime_error("cannot open server.properties: " + path.string()); }
    return parseServerProperties(input);
}

} // namespace mcserver::server
