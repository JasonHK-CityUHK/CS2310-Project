#include "mcserver/server/RegionFile.hpp"

#include "mcserver/protocol/Nbt.hpp"
#include "mcserver/server/WorldLock.hpp"

#include <zlib.h>
#include <lz4.h>
#define XXH_NAMESPACE MCSERVER_
#include <xxhash.h>

#include <array>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

namespace mcserver::server {
namespace {

constexpr uint64_t kSectorSize = 4096;
constexpr size_t kMaxChunkBytes = 32 * 1024 * 1024;

struct FileCloser {
    void operator()(std::FILE* file) const { std::fclose(file); }
};

int32_t regionCoordinate(int32_t coordinate) {
    int32_t quotient = coordinate / 32;
    return quotient - (coordinate % 32 < 0 ? 1 : 0);
}

uint32_t integerAt(char const* data) {
    return (static_cast<uint32_t>(static_cast<uint8_t>(data[0])) << 24) |
           (static_cast<uint32_t>(static_cast<uint8_t>(data[1])) << 16) |
           (static_cast<uint32_t>(static_cast<uint8_t>(data[2])) << 8) |
           static_cast<uint8_t>(data[3]);
}

void writeInteger(char* data, uint32_t value) {
    for (int index = 0; index < 4; ++index) { data[index] = static_cast<char>(value >> (24 - index * 8)); }
}

std::filesystem::path regionPath(std::filesystem::path const& worldDirectory, int32_t chunkX, int32_t chunkZ) {
    auto directory = worldDirectory / "dimensions" / "minecraft" / "overworld" / "region";
    return directory / ("r." + std::to_string(regionCoordinate(chunkX)) + "." +
                        std::to_string(regionCoordinate(chunkZ)) + ".mca");
}

void readExact(std::ifstream& input, char* data, size_t count) {
    if (!input.read(data, static_cast<std::streamsize>(count))) { throw std::runtime_error("truncated region file"); }
}

void writeExact(std::FILE* output, char const* data, size_t count) {
    if (std::fwrite(data, 1, count, output) != count) { throw std::runtime_error("cannot write temporary region"); }
}

std::string readExternal(std::filesystem::path const& path) {
    uint64_t size = std::filesystem::file_size(path);
    if (size > kMaxChunkBytes) { throw std::runtime_error("external chunk exceeds size limit"); }
    std::ifstream input(path, std::ios::binary);
    if (!input) { throw std::runtime_error("cannot open external chunk: " + path.string()); }
    std::string result(static_cast<size_t>(size), '\0');
    readExact(input, result.data(), result.size());
    return result;
}

std::string decompress(std::string const& compressed, int windowBits) {
    z_stream stream{};
    if (inflateInit2(&stream, windowBits) != Z_OK) { throw std::runtime_error("cannot initialize chunk decompression"); }
    struct Inflater {
        z_stream& stream;
        ~Inflater() { inflateEnd(&stream); }
    } inflater{stream};
    stream.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(compressed.data()));
    stream.avail_in = static_cast<uInt>(compressed.size());
    std::string result;
    std::array<char, 8192> buffer{};
    while (true) {
        stream.next_out = reinterpret_cast<Bytef*>(buffer.data());
        stream.avail_out = static_cast<uInt>(buffer.size());
        int status = inflate(&stream, Z_NO_FLUSH);
        size_t count = buffer.size() - stream.avail_out;
        if (count > kMaxChunkBytes - result.size()) { throw std::runtime_error("decompressed chunk exceeds size limit"); }
        result.append(buffer.data(), count);
        if (status == Z_STREAM_END) {
            if (stream.avail_in != 0) { throw std::runtime_error("trailing compressed chunk data"); }
            return result;
        }
        if (status != Z_OK || (count == 0 && stream.avail_in == 0)) {
            throw std::runtime_error("invalid or truncated compressed chunk");
        }
    }
}

std::string decompressLz4(std::string const& compressed) {
    constexpr size_t headerSize = 21;
    constexpr uint32_t seed = 0x9747b28c;
    size_t position = 0;
    std::string result;
    auto littleInteger = [&compressed](size_t offset) {
        uint32_t value = 0;
        for (size_t index = 0; index < 4; ++index) {
            value |= static_cast<uint32_t>(static_cast<uint8_t>(compressed[offset + index])) << (8 * index);
        }
        return value;
    };
    while (true) {
        if (compressed.size() - position < headerSize || compressed.compare(position, 8, "LZ4Block") != 0) {
            throw std::runtime_error("invalid LZ4 chunk header");
        }
        uint8_t token = static_cast<uint8_t>(compressed[position + 8]);
        uint8_t method = token & 0xf0;
        uint32_t compressedSize = littleInteger(position + 9);
        uint32_t originalSize = littleInteger(position + 13);
        uint32_t checksum = littleInteger(position + 17);
        position += headerSize;
        if ((method != 0x10 && method != 0x20) || originalSize > (uint32_t{1} << (10 + (token & 0x0f))) ||
            compressedSize > compressed.size() - position || originalSize > kMaxChunkBytes - result.size() ||
            (originalSize == 0) != (compressedSize == 0) || (method == 0x10 && originalSize != compressedSize)) {
            throw std::runtime_error("invalid LZ4 chunk block");
        }
        if (originalSize == 0) {
            if (checksum != 0 || position != compressed.size()) { throw std::runtime_error("invalid LZ4 chunk terminator"); }
            return result;
        }
        size_t start = result.size();
        result.resize(start + originalSize);
        if (method == 0x10) {
            std::copy_n(compressed.data() + position, originalSize, result.data() + start);
        } else {
            int decoded = LZ4_decompress_safe(compressed.data() + position, result.data() + start,
                                              static_cast<int>(compressedSize), static_cast<int>(originalSize));
            if (decoded != static_cast<int>(originalSize)) { throw std::runtime_error("invalid LZ4 chunk payload"); }
        }
        if ((XXH32(result.data() + start, originalSize, seed) & 0x0fffffffu) != checksum) {
            throw std::runtime_error("LZ4 chunk checksum mismatch");
        }
        position += compressedSize;
    }
}

int32_t requiredInteger(nbt::CompoundTag const& chunk, char const* name) {
    if (!chunk.contains(name, nbt::Tag::Type::Int)) { throw std::runtime_error(std::string("missing chunk integer ") + name); }
    return static_cast<int32_t>(chunk.at(name));
}

} // namespace

std::optional<nbt::CompoundTag> loadRegionChunk(std::filesystem::path const& worldDirectory,
                                                int32_t chunkX, int32_t chunkZ, bool* externalResult) {
    if (externalResult) { *externalResult = false; }
    int32_t regionX = regionCoordinate(chunkX);
    int32_t regionZ = regionCoordinate(chunkZ);
    auto path = regionPath(worldDirectory, chunkX, chunkZ);
    auto directory = path.parent_path();
    if (!std::filesystem::exists(path)) { return std::nullopt; }
    uint64_t size = std::filesystem::file_size(path);
    if (size < 2 * kSectorSize || size % kSectorSize != 0) { throw std::runtime_error("invalid region file size: " + path.string()); }
    std::ifstream input(path, std::ios::binary);
    if (!input) { throw std::runtime_error("cannot open region file: " + path.string()); }
    std::array<char, kSectorSize> locations{};
    readExact(input, locations.data(), locations.size());
    std::vector<std::pair<uint32_t, uint32_t>> allocations;
    allocations.reserve(1024);
    for (size_t index = 0; index < 1024; ++index) {
        uint32_t location = integerAt(locations.data() + index * 4);
        uint32_t offset = location >> 8;
        uint32_t count = location & 0xff;
        if (location == 0) { continue; }
        if (offset < 2 || count == 0 || static_cast<uint64_t>(offset) + count > size / kSectorSize) {
            throw std::runtime_error("invalid region sector allocation: " + path.string());
        }
        for (auto const& [otherOffset, otherCount] : allocations) {
            if (offset < otherOffset + otherCount && otherOffset < offset + count) {
                throw std::runtime_error("overlapping region sector allocations: " + path.string());
            }
        }
        allocations.emplace_back(offset, count);
    }
    uint32_t localX = static_cast<uint32_t>(chunkX - regionX * 32);
    uint32_t localZ = static_cast<uint32_t>(chunkZ - regionZ * 32);
    uint32_t location = integerAt(locations.data() + (localX + localZ * 32) * 4);
    if (location == 0) { return std::nullopt; }
    uint32_t offset = location >> 8;
    uint32_t sectors = location & 0xff;
    input.seekg(static_cast<std::streamoff>(static_cast<uint64_t>(offset) * kSectorSize));
    std::array<char, 5> chunkHeader{};
    readExact(input, chunkHeader.data(), chunkHeader.size());
    uint32_t length = integerAt(chunkHeader.data());
    if (length == 0 || static_cast<uint64_t>(length) + 4 > sectors * kSectorSize) {
        throw std::runtime_error("invalid region chunk length: " + path.string());
    }
    uint8_t compression = static_cast<uint8_t>(chunkHeader[4]);
    bool external = (compression & 0x80) != 0;
    if (externalResult) { *externalResult = external; }
    compression &= 0x7f;
    std::string compressed;
    if (external) {
        if (length != 1) { throw std::runtime_error("invalid external chunk marker"); }
        compressed = readExternal(directory / ("c." + std::to_string(chunkX) + "." + std::to_string(chunkZ) + ".mcc"));
    } else {
        compressed.resize(length - 1);
        readExact(input, compressed.data(), compressed.size());
    }
    std::string data;
    switch (compression) {
    case 1: data = decompress(compressed, 15 + 16); break;
    case 2: data = decompress(compressed, 15); break;
    case 3: data = std::move(compressed); break;
    case 4: data = decompressLz4(compressed); break;
    default: throw std::runtime_error("unsupported region chunk compression: " + std::to_string(compression));
    }
    auto chunk = protocol::fromJavaDiskNbt(data);
    if (requiredInteger(chunk, "DataVersion") != 5023 || requiredInteger(chunk, "xPos") != chunkX ||
        requiredInteger(chunk, "zPos") != chunkZ) {
        throw std::runtime_error("incompatible chunk version or coordinates");
    }
    if (!chunk.contains("Status", nbt::Tag::Type::String) ||
        static_cast<std::string const&>(chunk.at("Status")) != "minecraft:full") {
        throw std::runtime_error("chunk is not fully generated");
    }
    return chunk;
}

void saveRegionChunk(WorldLock const& lock, std::filesystem::path const& worldDirectory, int32_t chunkX, int32_t chunkZ,
                     nbt::CompoundTag const& chunk) {
    if (std::filesystem::canonical(worldDirectory) != lock.directory()) {
        throw std::runtime_error("world session lock does not match region directory");
    }
    if (!loadRegionChunk(worldDirectory, chunkX, chunkZ)) { throw std::runtime_error("cannot create missing chunk"); }
    if (requiredInteger(chunk, "DataVersion") != 5023 || requiredInteger(chunk, "xPos") != chunkX ||
        requiredInteger(chunk, "zPos") != chunkZ || !chunk.contains("Status", nbt::Tag::Type::String) ||
        static_cast<std::string const&>(chunk.at("Status")) != "minecraft:full") {
        throw std::runtime_error("invalid chunk being saved");
    }
    auto path = regionPath(worldDirectory, chunkX, chunkZ);
    uint64_t size = std::filesystem::file_size(path);
    if (size / kSectorSize > 0xffffff) { throw std::runtime_error("region file is too large"); }
    std::ifstream input(path, std::ios::binary);
    if (!input) { throw std::runtime_error("cannot open region for writing"); }
    std::array<char, kSectorSize * 2> header{};
    readExact(input, header.data(), header.size());
    int32_t regionX = regionCoordinate(chunkX);
    int32_t regionZ = regionCoordinate(chunkZ);
    size_t index = static_cast<size_t>(chunkX - regionX * 32) + static_cast<size_t>(chunkZ - regionZ * 32) * 32;
    uint32_t oldLocation = integerAt(header.data() + index * 4);
    input.seekg(static_cast<std::streamoff>(static_cast<uint64_t>(oldLocation >> 8) * kSectorSize + 4));
    char oldCompression = 0;
    readExact(input, &oldCompression, 1);
    if ((static_cast<uint8_t>(oldCompression) & 0x80) != 0) {
        throw std::runtime_error("saving external chunks is not supported");
    }
    std::string serialized = chunk.toBinaryNbt(false);
    if (serialized.size() > kMaxChunkBytes) { throw std::runtime_error("chunk exceeds size limit"); }
    uLongf compressedSize = compressBound(serialized.size());
    std::string compressed(compressedSize, '\0');
    if (compress2(reinterpret_cast<Bytef*>(compressed.data()), &compressedSize,
                  reinterpret_cast<Bytef const*>(serialized.data()), serialized.size(), Z_DEFAULT_COMPRESSION) != Z_OK) {
        throw std::runtime_error("cannot compress chunk");
    }
    compressed.resize(compressedSize);
    uint64_t sectors = (compressed.size() + 5 + kSectorSize - 1) / kSectorSize;
    if (sectors > 255) { throw std::runtime_error("chunk requires unsupported external storage"); }
    writeInteger(header.data() + index * 4, static_cast<uint32_t>((size / kSectorSize << 8) | sectors));
    auto timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    writeInteger(header.data() + kSectorSize + index * 4, static_cast<uint32_t>(timestamp));
    std::random_device random;
    auto temporary = path;
    temporary += ".tmp." + std::to_string(random()) + "." + std::to_string(random());
    bool opened = false;
    try {
    #ifdef _WIN32
        std::unique_ptr<std::FILE, FileCloser> output(_wfopen(temporary.c_str(), L"wbx"));
    #else
        std::unique_ptr<std::FILE, FileCloser> output(std::fopen(temporary.c_str(), "wbx"));
    #endif
        if (!output) { throw std::runtime_error("cannot create temporary region file"); }
        opened = true;
        writeExact(output.get(), header.data(), header.size());
        input.clear();
        input.seekg(static_cast<std::streamoff>(header.size()));
        std::array<char, 65536> buffer{};
        uint64_t remaining = size - header.size();
        while (remaining > 0) {
            size_t count = static_cast<size_t>(std::min<uint64_t>(remaining, buffer.size()));
            readExact(input, buffer.data(), count);
            writeExact(output.get(), buffer.data(), count);
            remaining -= count;
        }
        std::array<char, 5> chunkHeader{};
        writeInteger(chunkHeader.data(), static_cast<uint32_t>(compressed.size() + 1));
        chunkHeader[4] = 2;
        writeExact(output.get(), chunkHeader.data(), chunkHeader.size());
        writeExact(output.get(), compressed.data(), compressed.size());
        std::array<char, kSectorSize> padding{};
        size_t paddingSize = static_cast<size_t>(sectors * kSectorSize - compressed.size() - chunkHeader.size());
        writeExact(output.get(), padding.data(), paddingSize);
        if (std::fflush(output.get()) != 0) { throw std::runtime_error("cannot flush temporary region file"); }
        if (std::fclose(output.release()) != 0) { throw std::runtime_error("cannot close temporary region file"); }
        input.close();
#ifdef _WIN32
        if (!MoveFileExW(temporary.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
            throw std::runtime_error("cannot replace region file");
        }
#else
        std::filesystem::rename(temporary, path);
#endif
    } catch (...) {
        std::error_code ignored;
        if (opened) { std::filesystem::remove(temporary, ignored); }
        throw;
    }
}

} // namespace mcserver::server
