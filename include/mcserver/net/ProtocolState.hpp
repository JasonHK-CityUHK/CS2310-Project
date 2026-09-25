#pragma once

namespace mcserver::net {

// Which phase of the Java Edition protocol handshake a connection is in.
// Determines which packet ID -> meaning mapping applies.
enum class ProtocolState {
    Handshaking,
    Status,
    Login,
    Configuration,
    Play,
};

} // namespace mcserver::net
