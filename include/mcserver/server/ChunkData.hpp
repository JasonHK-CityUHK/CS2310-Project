#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <nbt/NBT.hpp>

#include "mcserver/net/ByteBuffer.hpp"

namespace mcserver::server {

class World;

std::vector<std::byte> makeFlatChunkData(World const& world, int32_t chunkX, int32_t chunkZ);
void writeJavaChunkLight(net::ByteWriter& writer, nbt::CompoundTag const& chunk);

} // namespace mcserver::server
