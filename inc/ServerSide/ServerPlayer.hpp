#pragma once

#include <iostream>
#include "Scene.hpp"

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
        gameObject = Scene::getInstance().gameObjectManager->Create2dObject("serverplayer");
        gameObject->SetTexture(Scene::getInstance().textureManager->loadTexture("./animations/Player/Idle/PlayerIdle0.png"));
        gameObject->SetShaderProgram(Scene::getInstance().shaderProgram);
        gameObject->setPosition(glm::vec3(posx, posy, 0));
    }
    void SetPosition(int x, int y)
    {
        gameObject->setPosition(glm::vec3(x, y, 0));
    }
    std::string username;
    int fd;
};