#include "mcserver/server/PlayerInventory.hpp"

namespace mcserver::server {

PlayerInventory::PlayerInventory() {
    hotbar[0] = {.itemId = 1, .count = 64};
}

} // namespace mcserver::server
