#pragma once

#include <iostream>
class ServerPlayer;
#include "Scene.hpp"
#include "Animator.hpp"

struct vector2
{
    int x, y;
};

class ServerPlayer
{
public:
    GameObject *gameObject;
    ServerPlayer(int fd, int posx, int posy)
    {
        this->fd = fd;
        this->username = "canodis";
        gameObject = Scene::getInstance().gameObjectManager->Create2dObject("player");
        gameObject->SetTexture(Scene::getInstance().textureManager->loadTexture("./animations/Player/Idle/PlayerIdle0.png"));
        Animator *anim = gameObject->AddComponent<Animator>();
        anim->loadTexturesFromDirectory(AnimationType::idle, "./animations/Player/Idle/", "PlayerIdle", "png", 0.2f);
        anim->loadTexturesFromDirectory(AnimationType::run, "./animations/Player/Run/", "PlayerRun", "png", 0.1f);
        anim->setCurrentAnimation(AnimationType::idle);
        anim->setServerPlayer(true);
        gameObject->SetShaderProgram(Scene::getInstance().shaderProgram);
        gameObject->setPosition(glm::vec3(posx, posy, 0));
    }

    void SetPosition(float x, float y)
    {
        gameObject->setPosition(glm::vec3(x, y, 0));
    }

    void SetAnimation(int anim)
    {
        Animator *animator = gameObject->GetComponent<Animator>();
        animator->setCurrentAnimation(anim);
    }

    std::string username;
    int fd;
};