#pragma once

#include "BasePackage.hpp"

struct PlayerPositionPackage : public BasePackage
{
    PlayerPositionPackage();
    PlayerPositionPackage(int fd, float targetX, float targetY, float positionX, float positionY);
    int pId;
    int fd;
    float targetX;
    float targetY;
    float positionX;
    float positionY;
    MSGPACK_DEFINE(pId, fd, targetX, targetY, positionX, positionY, MSGPACK_BASE(BasePackage));
};
