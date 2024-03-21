#include "NewBasicNpcPackage.hpp"

NewBasicNpcPackage::NewBasicNpcPackage(int id, float x, float y, float targetX, float targetY, float speed, float health, int type) : NewBasicNpcPackage()
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->targetX = targetX;
    this->targetY = targetY;
    this->speed = speed;
    this->health = health;
    this->type = type;
}

NewBasicNpcPackage::NewBasicNpcPackage() {
    packageId = ServerPackage::NewBasicNpc;
    pId = (int)packageId;
}