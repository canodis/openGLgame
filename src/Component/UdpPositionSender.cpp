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
    Animator *animator = gameObject->GetComponent<Animator>();
    int animType;
    if (animator == NULL)
        animType = 0;
    else
        animType = gameObject->GetComponent<Animator>()->getAnimationType();
    Client::getInstance().udpConnection->sendPlayerAllData(gameObject->transform.position.x,
        gameObject->transform.position.y, gameObject->transform.scale.x, animType, deltaTime);
}

void UdpPositionSender::setGameObject(GameObject *gObject)
{
    gameObject = gObject;
}

void UdpPositionSender::setStatic()
{
}
