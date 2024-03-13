#include "BasePacket.hpp"

BasePacket::BasePacket(ServerPackage packetId)
{
    this->packetId = packetId;
}

BasePacket::BasePacket() { }