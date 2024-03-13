#pragma once

#include "BasePacket.hpp"

class PlayerPositionPackage : public BasePacket
{
public:
    PlayerPositionPackage();
    PlayerPositionPackage(int fd, float targetX, float targetY, float positionX, float positionY);
    int fd;
    float targetX;
    float targetY;
    float positionX;
    float positionY;
    MSGPACK_DEFINE(fd, targetX, targetY, positionX, positionY);
};