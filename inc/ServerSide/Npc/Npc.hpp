#pragma once

#include "../../Data/vec2.hpp"
#include "Scene.hpp"
#include "Animator.hpp"

class Npc
{
public:
    Npc();
    virtual void update(float deltaTime) = 0;
    void setSpeed(float speed);
    int _id;
    dis::vec2 targetPosition;
    GameObject *obj;
protected:
    float speed;
};