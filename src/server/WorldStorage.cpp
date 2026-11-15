#include "mcserver/server/WorldStorage.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <limits>
#include <stdexcept>

namespace mcserver::server {
namespace {
using Json = nlohmann::json;

int32_t coordinate(Json const& value) {
    if (!value.is_number_integer()) { throw std::runtime_error("block coordinate must be an integer"); }
    if (value.is_number_unsigned()) {
        auto number = value.get<uint64_t>();
        if (number > static_cast<uint64_t>(std::numeric_limits<int32_t>::max())) {
            throw std::runtime_error("block coordinate exceeds integer range");
        }
        return static_cast<int32_t>(number);
    }
    auto number = value.get<int64_t>();
    if (number < std::numeric_limits<int32_t>::min() || number > std::numeric_limits<int32_t>::max()) {
        throw std::runtime_error("block coordinate exceeds integer range");
    }
    return static_cast<int32_t>(number);
}
} // namespace

bool WorldStorage::load(World& world) const {
    if (!std::filesystem::exists(file_)) { return false; }
    if (std::filesystem::file_size(file_) > 32 * 1024 * 1024) {
        throw std::runtime_error("world save exceeds the 32 MiB limit: " + file_.string());
    }
    std::ifstream input(file_, std::ios::binary);
    if (!input) { throw std::runtime_error("cannot read world save: " + file_.string()); }
    Json document = Json::parse(input);
    auto const& version = document.at("version");
    bool legacy = version.is_number_integer() && version == 1;
    if (!version.is_number_integer() || (!legacy && version != 2) ||
        document.value("world", std::string{}) != "flat-stone-v1" ||
        (!legacy && coordinate(document.at("protocol")) != 777)) {
        throw std::runtime_error("unsupported world save format: " + file_.string());
    }
    auto const& blocks = document.at(legacy ? "broken_blocks" : "blocks");
    if (!blocks.is_array() || blocks.size() > (legacy ? 2304u : 100000u)) {
        throw std::runtime_error("invalid block list in world save: " + file_.string());
    }
    std::vector<World::BlockChange> restored;
    for (auto const& block : blocks) {
        net::BlockPos position{coordinate(block.at("x")), coordinate(block.at("y")), coordinate(block.at("z"))};
        if (legacy && (position.x < -16 || position.x > 31 || position.z < -16 || position.z > 31 || position.y != 0)) {
            throw std::runtime_error("invalid legacy world position");
        }
        restored.push_back({position, legacy ? 0 : coordinate(block.at("state"))});
    }
    if (input.bad()) { throw std::runtime_error("error reading world save: " + file_.string()); }
    world.restoreChanges(restored);
    return true;
}

void WorldStorage::save(World const& world) const {
    Json blocks = Json::array();
    auto changes = world.blockChanges();
    if (changes.size() > 100000) { throw std::runtime_error("world save exceeds the block limit"); }
    for (auto const& change : changes) {
        auto const& position = change.position;
        blocks.push_back({{"x", position.x}, {"y", position.y}, {"z", position.z}, {"state", change.state}});
    }
    Json document{{"version", 2}, {"protocol", 777}, {"world", "flat-stone-v1"}, {"blocks", std::move(blocks)}};
    auto parent = file_.parent_path();
    if (!parent.empty()) { std::filesystem::create_directories(parent); }
    auto temporary = file_;
    temporary += ".tmp";
    bool temporaryOpened = false;
    try {
        std::ofstream output;
        output.exceptions(std::ios::failbit | std::ios::badbit);
        output.open(temporary, std::ios::binary | std::ios::trunc);
        temporaryOpened = true;
        output << document.dump(2) << '\n';
        output.flush();
        output.close();
        std::filesystem::rename(temporary, file_);
    } catch (...) {
        std::error_code ignored;
        if (temporaryOpened) { std::filesystem::remove(temporary, ignored); }
        throw;
    }
}

} // namespace mcserver::server
