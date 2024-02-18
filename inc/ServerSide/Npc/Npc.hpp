#pragma once

#include "../../Data/vec2.hpp"
#include "Scene.hpp"
#include "Animator.hpp"

class Npc
{
public:
    Npc();
    int _id;
    virtual void update(float deltaTime) = 0;
    void setSpeed(float speed);
    void setHealth(float health);

    float getHealth() const;

    dis::vec2 targetPosition;
    GameObject *obj;
protected:
    float speed;
    float health;
};