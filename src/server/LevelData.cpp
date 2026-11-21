#include "mcserver/server/LevelData.hpp"

#include "mcserver/protocol/Nbt.hpp"

#include <zlib.h>

#include <array>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <cstdint>

namespace mcserver::server {
namespace {

constexpr size_t kMaxLevelBytes = 32 * 1024 * 1024;
constexpr int32_t kDataVersion = 5023;

std::string readLevelNbt(std::filesystem::path const& path) {
    if (std::filesystem::file_size(path) > kMaxLevelBytes) {
        throw std::runtime_error("compressed level.dat exceeds size limit");
    }
    std::ifstream input(path, std::ios::binary);
    std::array<unsigned char, 2> header{};
    if (!input.read(reinterpret_cast<char*>(header.data()), header.size()) || header[0] != 0x1f || header[1] != 0x8b) {
        throw std::runtime_error("level.dat is not gzip-compressed");
    }
    input.close();
    std::unique_ptr<gzFile_s, decltype(&gzclose)> file(gzopen(path.string().c_str(), "rb"), &gzclose);
    if (!file) { throw std::runtime_error("cannot open level.dat"); }
    std::string result;
    std::array<char, 8192> buffer{};
    while (true) {
        int count = gzread(file.get(), buffer.data(), static_cast<unsigned>(buffer.size()));
        if (count < 0) { throw std::runtime_error("cannot decompress level.dat"); }
        if (count == 0) {
            int error = Z_OK;
            gzerror(file.get(), &error);
            if (error != Z_OK && error != Z_STREAM_END) { throw std::runtime_error("truncated level.dat"); }
            break;
        }
        if (static_cast<size_t>(count) > kMaxLevelBytes - result.size()) {
            throw std::runtime_error("decompressed level.dat exceeds size limit");
        }
        result.append(buffer.data(), static_cast<size_t>(count));
    }

    uint64_t compressedSize = std::filesystem::file_size(path);
    if (compressedSize < 18) {
        throw std::runtime_error("truncated level.dat");
    }
    std::ifstream footerInput(path, std::ios::binary);
    if (!footerInput) {
        throw std::runtime_error("cannot verify level.dat");
    }
    footerInput.seekg(static_cast<std::streamoff>(compressedSize - 8));
    std::array<unsigned char, 8> footer{};
    if (!footerInput.read(reinterpret_cast<char*>(footer.data()), footer.size())) {
        throw std::runtime_error("truncated level.dat");
    }
    uint32_t expectedCrc = static_cast<uint32_t>(footer[0]) |
                            (static_cast<uint32_t>(footer[1]) << 8) |
                            (static_cast<uint32_t>(footer[2]) << 16) |
                            (static_cast<uint32_t>(footer[3]) << 24);
    uint32_t expectedSize = static_cast<uint32_t>(footer[4]) |
                            (static_cast<uint32_t>(footer[5]) << 8) |
                            (static_cast<uint32_t>(footer[6]) << 16) |
                            (static_cast<uint32_t>(footer[7]) << 24);
    uLong actualCrc = crc32(0L, Z_NULL, 0);
    actualCrc = crc32(actualCrc, reinterpret_cast<Bytef const*>(result.data()),
                      static_cast<uInt>(result.size()));
    if (static_cast<uint32_t>(actualCrc) != expectedCrc ||
        expectedSize != static_cast<uint32_t>(result.size())) {
        throw std::runtime_error("truncated or corrupted level.dat");
    }
    return result;
}

nbt::CompoundTag const& compound(nbt::CompoundTag const& parent, char const* name) {
    if (!parent.contains(name, nbt::Tag::Type::Compound)) { throw std::runtime_error(std::string("missing compound ") + name); }
    return parent.at(name).as<nbt::CompoundTag>();
}

int32_t integer(nbt::CompoundTag const& parent, char const* name) {
    if (!parent.contains(name, nbt::Tag::Type::Int)) { throw std::runtime_error(std::string("missing integer ") + name); }
    return static_cast<int32_t>(parent.at(name));
}

float floating(nbt::CompoundTag const& parent, char const* name) {
    if (!parent.contains(name, nbt::Tag::Type::Float)) { throw std::runtime_error(std::string("missing float ") + name); }
    return static_cast<float>(parent.at(name));
}

} // namespace

LevelData loadLevelData(std::filesystem::path const& worldDirectory) {
    auto root = protocol::fromJavaDiskNbt(readLevelNbt(worldDirectory / "level.dat"));
    auto const& data = compound(root, "Data");
    int32_t version = integer(data, "DataVersion");
    if (version != kDataVersion) { throw std::runtime_error("unsupported world data version: " + std::to_string(version)); }
    auto const& spawn = compound(data, "spawn");
    if (!spawn.contains("dimension", nbt::Tag::Type::String) || !spawn.contains("pos", nbt::Tag::Type::IntArray)) {
        throw std::runtime_error("missing world spawn dimension or position");
    }
    auto const& position = spawn.at("pos").as<nbt::IntArrayTag>().storage();
    if (position.size() != 3) { throw std::runtime_error("invalid world spawn position"); }
    return {version, static_cast<std::string const&>(spawn.at("dimension")), position[0], position[1], position[2],
            floating(spawn, "yaw"), floating(spawn, "pitch")};
}

} // namespace mcserver::server
