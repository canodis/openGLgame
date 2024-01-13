#pragma once

class Component;
#include "GameObject.hpp"

class Component {
public:
    virtual ~Component() {}
    Component() {}
    Component(GameObject *gameObject) {}
    virtual void setGameObject(GameObject *gameObject) = 0;
    virtual void update(float deltaTime) = 0;
    GameObject *object;
};
