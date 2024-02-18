#include "ServerPlayer.hpp"

ServerPlayer::ServerPlayer(int fd, float posx, float posy)
{
    this->fd = fd;
    this->username = "canodis";
    speed = 3.0f;
    gameObject = Scene::getInstance().gameObjectManager->Create2dObject("player");
    gameObject->SetTexture(Scene::getInstance().textureManager->loadTexture("./animations/Player/Idle/PlayerIdle0.png"));
    gameObject->AddComponent<BoxCollision2d>()->setCollisionScale(glm::vec2(0.8f, 0.9f));
    Animator *anim = gameObject->AddComponent<Animator>();
    anim->loadTexturesFromDirectory(AnimationType::idle, "./animations/Player/Idle/", "PlayerIdle", "png", 0.2f);
    anim->loadTexturesFromDirectory(AnimationType::run, "./animations/Player/Run/", "PlayerRun", "png", 0.1f);
    anim->setCurrentAnimation(AnimationType::idle);
    gameObject->SetShaderProgram(Scene::getInstance().shaderProgram);
    gameObject->setPosition(glm::vec3(posx, posy, 0));
    targetPosition = gameObject->transform.position;
}

ServerPlayer::ServerPlayer(int fd, float posx, float posy, float targetx, float targety) : ServerPlayer(fd, posx, posy)
{
    targetPosition = glm::vec3(targetx, targety, 0);
}

void ServerPlayer::SetPosition(float x, float y)
{
    gameObject->setPosition(glm::vec3(x, y, 0));
}

void ServerPlayer::SetScale(int x)
{
    gameObject->transform.scale.x = x;
}

void ServerPlayer::SetTargetPosition(float posx, float posy, float targetx, float targety)
{
    targetPosition = glm::vec3(targetx, targety, 0);
    SetPosition(posx, posy);
}

void ServerPlayer::SetAnimation(int anim)
{
    Animator *animator = gameObject->GetComponent<Animator>();
    animator->setCurrentAnimation(anim);
}

void ServerPlayer::update(float deltaTime)
{
    move(deltaTime);
    gameObject->update(deltaTime);
}

void ServerPlayer::move(float deltaTime)
{
    gameObject->move(targetPosition, deltaTime, speed);

    Animator *anim = gameObject->GetComponent<Animator>();
    if (gameObject->velocity.x != 0 || gameObject->velocity.y != 0)
    {
        anim->setCurrentAnimation(AnimationType::run);
    }
    else
    {
        anim->setCurrentAnimation(AnimationType::idle);
    }
    gameObject->velocity = glm::vec3(0);
}
