#pragma once

#include "BasePacket.hpp"

class BasicNpcPositionPackage : public BasePacket
{
public:
    BasicNpcPositionPackage();
    BasicNpcPositionPackage(int id, float x, float y, float targetX, float targetY);
    int id;
    float x;
    float y;
    float targetX;
    float targetY;
    MSGPACK_DEFINE(id, x, y, targetX, targetY);
};