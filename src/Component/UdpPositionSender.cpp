#include "UdpPositionSender.hpp"

UdpPositionSender::UdpPositionSender()
{
    lastPosition = glm::vec3(0, 0, 0);
}

UdpPositionSender::UdpPositionSender(GameObject *gObject) : gameObject(gObject)
{
}

UdpPositionSender::~UdpPositionSender()
{
}

void UdpPositionSender::update(float deltaTime)
{
    if (gameObject->transform.position == lastPosition)
        return;
    lastPosition = gameObject->transform.position;
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
