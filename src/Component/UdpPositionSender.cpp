#include "UdpPositionSender.hpp"

UdpPositionSender::UdpPositionSender()
{
}

UdpPositionSender::UdpPositionSender(GameObject *gObject) : gameObject(gObject)
{
}

UdpPositionSender::~UdpPositionSender()
{
}

void UdpPositionSender::update(float deltaTime)
{
    Client::getInstance().udpConnection->sendPlayerPosition(gameObject->transform.position.x,
        gameObject->transform.position.y, deltaTime);
}

void UdpPositionSender::setGameObject(GameObject *gObject)
{
    gameObject = gObject;
}

void UdpPositionSender::setStatic()
{
}
