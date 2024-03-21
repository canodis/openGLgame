#pragma once

#include "Package.hpp"

struct BasicNpcPositionPackage
{
    BasicNpcPositionPackage();
    BasicNpcPositionPackage(int id, float x, float y, float targetX, float targetY);
    int packageId;
    int id;
    float x;
    float y;
    float targetX;
    float targetY;
    MSGPACK_DEFINE(packageId, id, x, y, targetX, targetY);
};