#pragma once

class Component;
#include "GameObject.hpp"

class Component
{
public:
    Component() {}
    Component(GameObject *gameObject) {}
    virtual ~Component() {}

    virtual void update(float deltaTime) = 0;
    virtual void setStatic() = 0;
    virtual void setGameObject(GameObject *gameObject);
    GameObject *object;
};
