#pragma once

#include "Package.hpp"

struct NewBasicNpcPackage
{
    NewBasicNpcPackage();
    NewBasicNpcPackage(int id, float x, float y, float targetX, float targetY, float speed, float health, int type);
    int packageId;
    int id;
    float x; 
    float y;
    int type;
    float targetX;
    float targetY;
    float speed;
    float health;
    MSGPACK_DEFINE(packageId ,id , x, y, type, targetX, targetY, speed, health);
};