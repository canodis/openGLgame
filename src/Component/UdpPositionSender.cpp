#include "UdpPositionSender.hpp"

UdpPositionSender::UdpPositionSender()
{
    lastPosition = glm::vec3(0, 0, 0);
    lastSend = false;
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
    {
        if (lastSend == false)
        {
            lastSend = true;
            Client::getInstance().udpConnection->sendPlayerAllData(gameObject->transform.position.x,
                gameObject->transform.position.y, gameObject->transform.scale.x, 0, deltaTime, true);
        }
        return;
    }
    lastPosition = gameObject->transform.position;
    Client::getInstance().udpConnection->sendPlayerAllData(gameObject->transform.position.x,
        gameObject->transform.position.y, gameObject->transform.scale.x, getAnimationType(), deltaTime, false);
    lastSend = false;
}

void UdpPositionSender::setGameObject(GameObject *gObject)
{
    gameObject = gObject;
}

void UdpPositionSender::setStatic()
{
}

int UdpPositionSender::getAnimationType()
{
    Animator *animator = gameObject->GetComponent<Animator>();
    if (animator == NULL)
        return 0;
    return animator->getAnimationType();
}