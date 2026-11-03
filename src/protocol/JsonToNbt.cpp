#include "mcserver/protocol/JsonToNbt.hpp"

#include <nlohmann/json.hpp>

#include <cstdint>
#include <limits>
#include <vector>

namespace mcserver::protocol {

nbt::CompoundTagVariant jsonValueToNbt(nlohmann::json const& value) {
    using nbt::CompoundTagVariant;

    if (value.is_boolean()) { return CompoundTagVariant(static_cast<int8_t>(value.get<bool>() ? 1 : 0)); }
    if (value.is_number_integer() || value.is_number_unsigned()) {
        int64_t asLong = value.get<int64_t>();
        if (asLong >= std::numeric_limits<int32_t>::min() && asLong <= std::numeric_limits<int32_t>::max()) {
            return CompoundTagVariant(static_cast<int32_t>(asLong));
        }
        return CompoundTagVariant(nbt::LongTag(asLong));
    }
    if (value.is_number_float()) { return CompoundTagVariant(value.get<double>()); }
    if (value.is_string()) { return CompoundTagVariant(value.get<std::string>()); }
    if (value.is_array()) {
        std::vector<CompoundTagVariant> elements;
        elements.reserve(value.size());
        for (auto const& element : value) { elements.push_back(jsonValueToNbt(element)); }
        return CompoundTagVariant(nbt::ListTag(elements));
    }
    if (value.is_object()) { return CompoundTagVariant(jsonToNbt(value)); }
    // Null or otherwise unrepresentable values become an empty/absent tag.
    return CompoundTagVariant();
}

nbt::CompoundTag jsonToNbt(nlohmann::json const& object) {
    nbt::CompoundTag tag;
    for (auto const& [key, value] : object.items()) { tag[key] = jsonValueToNbt(value); }
    return tag;
}

} // namespace mcserver::protocol
