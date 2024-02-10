#pragma once

#include <iostream>
class ServerPlayer;
#include "Scene.hpp"
#include "Animator.hpp"
#include "BoxCollision2d.hpp"

struct vector2
{
    int x, y;
};

class ServerPlayer
{
public:
    GameObject *gameObject;
    glm::vec3 targetPosition;

    ServerPlayer(int fd, int posx, int posy);

    void SetPosition(float x, float y);
    void SetScale(int x);
    void SetTargetPosition(float posx, float posy, float targetx, float targety);
    void SetAnimation(int anim);
    void update(float deltaTime);
    void move(float deltaTime);

    std::string username;
    int fd;

private:
    bool isMoving;
    float speed;
};