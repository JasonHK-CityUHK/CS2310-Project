#include "mcserver/server/AnvilWorld.hpp"
#include "mcserver/util/Md5.hpp"

#include <nbt/NBT.hpp>
#include <nlohmann/json.hpp>
#include <zlib.h>

#include <algorithm>
#include <bit>
#include <bitset>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace mcserver::server {
namespace {
using Json = nlohmann::json;
constexpr size_t kMaxNbtSize = 16 * 1024 * 1024;

std::string readFile(std::filesystem::path const& path) {
    auto size = std::filesystem::file_size(path);
    if (size > kMaxNbtSize) { throw std::runtime_error("NBT file too large: " + path.string()); }
    std::ifstream file(path, std::ios::binary);
    if (!file) { throw std::runtime_error("cannot read " + path.string()); }
    std::string result(static_cast<size_t>(size), '\0');
    file.read(result.data(), static_cast<std::streamsize>(result.size()));
    if (!file) { throw std::runtime_error("truncated file: " + path.string()); }
    return result;
}

std::string decompress(std::string const& input, int compression) {
    if (compression == 3) {
        if (input.size() > kMaxNbtSize) { throw std::runtime_error("NBT payload too large"); }
        return input;
    }
    if (compression != 1 && compression != 2) {
        throw std::runtime_error("unsupported region compression (supported: gzip, zlib, uncompressed)");
    }
    z_stream stream{};
    if (inflateInit2(&stream, compression == 1 ? 31 : 15) != Z_OK) {
        throw std::runtime_error("cannot initialize chunk decompressor");
    }
    struct End { z_stream* stream; ~End() { inflateEnd(stream); } } end{&stream};
    stream.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(input.data()));
    stream.avail_in = static_cast<uInt>(input.size());
    std::string output;
    std::array<char, 8192> buffer{};
    int result;
    do {
        stream.next_out = reinterpret_cast<Bytef*>(buffer.data());
        stream.avail_out = static_cast<uInt>(buffer.size());
        result = inflate(&stream, Z_NO_FLUSH);
        if (result != Z_OK && result != Z_STREAM_END) { throw std::runtime_error("corrupt compressed NBT"); }
        output.append(buffer.data(), buffer.size() - stream.avail_out);
        if (output.size() > kMaxNbtSize) { throw std::runtime_error("decompressed NBT exceeds 16 MiB"); }
    } while (result != Z_STREAM_END);
    return output;
}

Json parseNbt(std::string const& bytes) {
    if (bytes.size() < 3 || static_cast<unsigned char>(bytes[0]) != 10) {
        throw std::runtime_error("expected named-root Java disk NBT compound");
    }
    auto tag = nbt::CompoundTag::fromBinaryNbt(bytes, false);
    return Json::parse(nbt::CompoundTagVariant(tag).toJson(0));
}

uint32_t bigEndian(char const* bytes) {
    uint32_t value = 0;
    for (int index = 0; index < 4; ++index) { value = (value << 8) | static_cast<uint8_t>(bytes[index]); }
    return value;
}

std::string readChunk(std::filesystem::path const& region, int32_t x, int32_t z) {
    int32_t rx = AnvilWorld::floorDiv(x, 32), rz = AnvilWorld::floorDiv(z, 32);
    auto path = region / ("r." + std::to_string(rx) + "." + std::to_string(rz) + ".mca");
    std::ifstream file(path, std::ios::binary);
    if (!file) { throw std::runtime_error("missing region: " + path.string()); }
    uint64_t fileSize = std::filesystem::file_size(path);
    if (fileSize < 8192) { throw std::runtime_error("truncated region header: " + path.string()); }
    int32_t localX = x - rx * 32, localZ = z - rz * 32;
    file.seekg((localX + localZ * 32) * 4);
    std::array<char, 4> entry{};
    file.read(entry.data(), 4);
    uint32_t location = bigEndian(entry.data());
    uint64_t offset = static_cast<uint64_t>(location >> 8) * 4096;
    uint32_t sectors = location & 255;
    if (location == 0) { throw std::runtime_error("required chunk is not generated: " + std::to_string(x) + "," + std::to_string(z)); }
    if (offset < 8192 || sectors == 0 || offset + sectors * 4096 > fileSize) {
        throw std::runtime_error("invalid chunk sector location");
    }
    file.seekg(static_cast<std::streamoff>(offset));
    file.read(entry.data(), 4);
    uint32_t length = bigEndian(entry.data());
    if (!file || length < 2 || length > sectors * 4096 - 4) { throw std::runtime_error("invalid chunk length"); }
    int compression = file.get();
    if (compression & 128) { throw std::runtime_error("external .mcc chunks are not supported yet"); }
    std::string payload(length - 1, '\0');
    file.read(payload.data(), static_cast<std::streamsize>(payload.size()));
    if (!file) { throw std::runtime_error("truncated chunk payload"); }
    return decompress(payload, compression);
}

std::vector<int32_t> unpack(Json const& container, std::vector<int32_t> const& palette,
                            size_t count, unsigned minimumBits) {
    if (palette.empty() || palette.size() > count) { throw std::runtime_error("invalid disk palette size"); }
    if (palette.size() == 1) { return std::vector<int32_t>(count, palette.front()); }
    unsigned bits = std::max(minimumBits, static_cast<unsigned>(std::bit_width(palette.size() - 1)));
    size_t perLong = 64 / bits;
    auto const& data = container.at("data");
    if (!data.is_array() || data.size() != (count + perLong - 1) / perLong) {
        throw std::runtime_error("invalid disk palette packed-array length");
    }
    std::vector<int32_t> values(count);
    for (size_t index = 0; index < count; ++index) {
        uint64_t word = static_cast<uint64_t>(data.at(index / perLong).get<int64_t>());
        auto id = static_cast<size_t>((word >> ((index % perLong) * bits)) & ((uint64_t{1} << bits) - 1));
        if (id >= palette.size()) { throw std::runtime_error("disk palette index out of range"); }
        values[index] = palette[id];
    }
    return values;
}

void validateSpawn(AnvilWorld::Spawn const& spawn) {
    if (!std::isfinite(spawn.x) || !std::isfinite(spawn.y) || !std::isfinite(spawn.z) ||
        !std::isfinite(spawn.yaw) || !std::isfinite(spawn.pitch) || std::abs(spawn.x) > 33554000 ||
        std::abs(spawn.z) > 33554000 || spawn.y < -64 || spawn.y >= 320) {
        throw std::runtime_error("invalid or unsupported overworld spawn position");
    }
}
} // namespace

int32_t AnvilWorld::floorDiv(int32_t value, int32_t divisor) {
    int32_t result = value / divisor;
    return value % divisor < 0 ? result - 1 : result;
}
uint64_t AnvilWorld::key(int32_t x, int32_t z) {
    return (uint64_t{static_cast<uint32_t>(x)} << 32) | static_cast<uint32_t>(z);
}

AnvilWorld::AnvilWorld(std::filesystem::path const& directory, BlockResolver resolveBlock, BiomeResolver resolveBiome) {
    auto metadata = parseNbt(decompress(readFile(directory / "level.dat"), 1)).at("Data");
    if (metadata.at("DataVersion") != 5023) { throw std::runtime_error("only Minecraft 26.3 DataVersion 5023 is supported"); }
    name_ = metadata.at("LevelName").get<std::string>();
    auto const& spawn = metadata.at("spawn");
    if (spawn.at("dimension") != "minecraft:overworld") { throw std::runtime_error("only Overworld imports are supported"); }
    auto const& pos = spawn.at("pos");
    spawn_ = {pos.at(0).get<int32_t>() + 0.5, pos.at(1).get<int32_t>() * 1.0,
              pos.at(2).get<int32_t>() + 0.5, spawn.value("yaw", 0.0f), spawn.value("pitch", 0.0f)};
    // A single-player sample should open at its last saved viewpoint, when available.
    if (metadata.contains("singleplayer_uuid")) {
        auto const& uuid = metadata.at("singleplayer_uuid");
        if (!uuid.is_array() || uuid.size() != 4) { throw std::runtime_error("invalid singleplayer_uuid"); }
        std::ostringstream hex;
        for (auto const& part : uuid) { hex << std::hex << std::setfill('0') << std::setw(8) << static_cast<uint32_t>(part.get<int32_t>()); }
        auto id = hex.str();
        auto file = directory / "players/data" / (id.substr(0,8) + "-" + id.substr(8,4) + "-" + id.substr(12,4) + "-" + id.substr(16,4) + "-" + id.substr(20) + ".dat");
        if (std::filesystem::exists(file)) {
            auto player = parseNbt(decompress(readFile(file), 1));
            if (player.value("Dimension", std::string{}) == "minecraft:overworld") {
                auto const& position = player.at("Pos");
                auto const& rotation = player.at("Rotation");
                spawn_ = {position.at(0).get<double>(), position.at(1).get<double>(), position.at(2).get<double>(),
                          rotation.at(0).get<float>(), rotation.at(1).get<float>()};
            }
        }
    }
    validateSpawn(spawn_);
    int32_t centerX = floorDiv(static_cast<int32_t>(std::floor(spawn_.x)), 16);
    int32_t centerZ = floorDiv(static_cast<int32_t>(std::floor(spawn_.z)), 16);
    std::string fingerprint;
    auto region = directory / "dimensions/minecraft/overworld/region";
    for (int32_t z = centerZ - 1; z <= centerZ + 1; ++z) {
        for (int32_t x = centerX - 1; x <= centerX + 1; ++x) {
            auto raw = readChunk(region, x, z);
            auto root = parseNbt(raw);
            if (root.at("DataVersion") != 5023 || root.at("xPos") != x || root.at("zPos") != z ||
                root.at("Status") != "minecraft:full") { throw std::runtime_error("chunk version, coordinates, or generation status mismatch"); }
            fingerprint += raw;
            Chunk chunk;
            std::bitset<24> seen;
            for (auto const& section : root.at("sections")) {
                int sectionY = section.at("Y").get<int>();
                // The NBT library exposes TAG_Byte as uint8_t in JSON; section Y is signed.
                if (sectionY >= 128 && sectionY <= 255) { sectionY -= 256; }
                int index = sectionY + 4;
                if (index < 0 || index >= 24) { continue; } // boundary lighting sections
                if (seen.test(index)) { throw std::runtime_error("duplicate chunk section"); }
                seen.set(index);
                std::vector<int32_t> palette;
                for (auto const& entry : section.at("block_states").at("palette")) {
                    std::string name;
                    Properties properties;
                    if (entry.is_string()) { name = entry.get<std::string>(); }
                    else {
                        name = entry.contains("id") ? entry.at("id").get<std::string>() : entry.at("").get<std::string>();
                        if (entry.contains("properties")) {
                            for (auto const& [property, value] : entry.at("properties").items()) { properties[property] = value.get<std::string>(); }
                        }
                    }
                    palette.push_back(resolveBlock(name, properties));
                }
                auto blocks = unpack(section.at("block_states"), palette, 4096, 4);
                std::copy(blocks.begin(), blocks.end(), chunk.blocks.begin() + index * 4096);
                palette.clear();
                for (auto const& biome : section.at("biomes").at("palette")) { palette.push_back(resolveBiome(biome.get<std::string>())); }
                auto biomes = unpack(section.at("biomes"), palette, 64, 1);
                std::copy(biomes.begin(), biomes.end(), chunk.biomes.begin() + index * 64);
            }
            if (!seen.all()) { throw std::runtime_error("missing terrain sections in imported chunk"); }
            chunks_.emplace(key(x,z), std::move(chunk));
        }
    }
    std::ostringstream id;
    id << "anvil-5023:";
    for (auto byte : util::md5(fingerprint)) { id << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned>(byte); }
    identity_ = id.str();
}

bool AnvilWorld::contains(net::BlockPos const& position) const {
    return position.y >= -64 && position.y < 320 && chunks_.contains(key(floorDiv(position.x,16), floorDiv(position.z,16)));
}
int32_t AnvilWorld::blockStateAt(net::BlockPos const& position) const {
    if (!contains(position)) { return 0; }
    int32_t cx = floorDiv(position.x,16), cz = floorDiv(position.z,16);
    size_t index = static_cast<size_t>((position.y + 64) * 256 + (position.z - cz * 16) * 16 + position.x - cx * 16);
    return chunks_.at(key(cx,cz)).blocks[index];
}
int32_t AnvilWorld::biomeAt(int32_t x, int32_t y, int32_t z) const {
    if (!contains({x,y,z})) { return 41; }
    int32_t cx = floorDiv(x,16), cz = floorDiv(z,16);
    size_t index = static_cast<size_t>(((y+64)/16)*64 + ((y+64)%16/4)*16 + ((z-cz*16)/4)*4 + (x-cx*16)/4);
    return chunks_.at(key(cx,cz)).biomes[index];
}

} // namespace mcserver::server
