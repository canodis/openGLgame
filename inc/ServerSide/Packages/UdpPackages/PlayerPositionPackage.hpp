#pragma once

#include "Package.hpp"

struct PlayerPositionPackage 
{
    PlayerPositionPackage();
    PlayerPositionPackage(int fd, float targetX, float targetY, float positionX, float positionY);
    int packageId;
    int fd;
    float targetX;
    float targetY;
    float positionX;
    float positionY;
    MSGPACK_DEFINE(packageId, fd, targetX, targetY, positionX, positionY);
};
