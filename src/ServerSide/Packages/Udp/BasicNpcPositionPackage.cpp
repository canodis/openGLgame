#include "BasicNpcPositionPackage.hpp"

BasicNpcPositionPackage::BasicNpcPositionPackage(int id, float x, float y, float targetX, float targetY) : BasicNpcPositionPackage()
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->targetX = targetX;
    this->targetY = targetY;
}

BasicNpcPositionPackage::BasicNpcPositionPackage() {
    packageId = ServerPackage::BasicNpcPosition;
}