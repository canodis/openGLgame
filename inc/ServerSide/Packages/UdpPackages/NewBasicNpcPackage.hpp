#pragma once

#include "BasePackage.hpp"

struct NewBasicNpcPackage : public BasePackage
{
    NewBasicNpcPackage();
    NewBasicNpcPackage(int id, float x, float y, float targetX, float targetY, float speed, float health, int type);
    int pId;
    int id;
    float x; 
    float y;
    int type;
    float targetX;
    float targetY;
    float speed;
    float health;
    MSGPACK_DEFINE(pId, id, x, y, type, targetX, targetY, speed, health, MSGPACK_BASE(BasePackage));
};
