#include "mcserver/net/Connection.hpp"
#include "mcserver/server/World.hpp"

#include <asio.hpp>
#include <catch2/catch_test_macros.hpp>

using namespace mcserver;

TEST_CASE("World stores broken blocks as air", "[world]") {
    server::World world;
    net::BlockPos position{.x = 3, .y = 0, .z = -2};

    REQUIRE(world.blockStateAt(position) == 1);
    world.setBlockToAir(position);
    REQUIRE(world.blockStateAt(position) == 0);
    REQUIRE(world.blockStateAt({.x = 4, .y = 0, .z = -2}) == 1);
}

TEST_CASE("World maps a vanilla block item and places it only into air", "[world]") {
    server::World world;
    auto stoneState = world.blockStateForItem(1);
    REQUIRE(stoneState == 1);

    net::BlockPos position{.x = 3, .y = 1, .z = -2};
    REQUIRE(world.tryPlaceBlock(position, *stoneState));
    REQUIRE(world.blockStateAt(position) == *stoneState);
    REQUIRE_FALSE(world.tryPlaceBlock(position, *stoneState));
}

TEST_CASE("World returns every other connected player", "[world]") {
    asio::io_context ioContext;
    auto first = std::make_shared<net::Connection>(asio::ip::tcp::socket(ioContext));
    auto second = std::make_shared<net::Connection>(asio::ip::tcp::socket(ioContext));
    server::World world;

    world.addPlayer(first);
    world.addPlayer(second);

    auto others = world.playersExcept(first.get());
    REQUIRE(others.size() == 1);
    REQUIRE(others.front() == second);

    world.removePlayer(second.get());
    REQUIRE(world.playersExcept(first.get()).empty());
}
