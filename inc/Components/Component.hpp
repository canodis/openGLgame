#pragma once

class Component;
#include "GameObject.hpp"

class Component {
public:
    Component();
    Component(GameObject *gameObject);
    virtual ~Component();
    virtual void setGameObject(GameObject *gameObject) = 0;
    virtual void update(float deltaTime) = 0;

    GameObject *object;
};
