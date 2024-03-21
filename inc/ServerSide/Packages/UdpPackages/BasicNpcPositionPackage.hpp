#pragma once

#include "BasePackage.hpp"

struct BasicNpcPositionPackage : public BasePackage
{
    BasicNpcPositionPackage();
    BasicNpcPositionPackage(int id, float x, float y, float targetX, float targetY);
    int pId;
    int id;
    float x;
    float y;
    float targetX;
    float targetY;
    MSGPACK_DEFINE(pId, id, x, y, targetX, targetY, MSGPACK_BASE(BasePackage));
};