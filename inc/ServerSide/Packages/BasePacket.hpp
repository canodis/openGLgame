#pragma once

#include <msgpack.hpp>
#include "ServerPackages.hpp"

class BasePacket
{
public:
    BasePacket();
    BasePacket(ServerPackage packetId);
    int packetId;
    MSGPACK_DEFINE(packetId);
};