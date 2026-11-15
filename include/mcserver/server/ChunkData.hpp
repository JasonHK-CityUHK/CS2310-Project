#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace mcserver::server {

class World;

std::vector<std::byte> makeFlatChunkData(World const& world, int32_t chunkX, int32_t chunkZ);

} // namespace mcserver::server
