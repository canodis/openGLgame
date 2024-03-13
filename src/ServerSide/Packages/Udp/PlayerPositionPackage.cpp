#include "PlayerPositionPackage.hpp"

PlayerPositionPackage::PlayerPositionPackage(int fd, float targetX, float targetY, float positionX, float positionY) : PlayerPositionPackage()
{
    this->fd = fd;
    this->targetX = targetX;
    this->targetY = targetY;
    this->positionX = positionX;
    this->positionY = positionY;
}

PlayerPositionPackage::PlayerPositionPackage() : BasePacket(ServerPackage::PositionRequest) {}