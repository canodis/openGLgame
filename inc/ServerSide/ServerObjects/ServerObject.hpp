#pragma once

#include "GameObject.hpp"

class ServerObject
{
public:
    ServerObject();
    ~ServerObject();

    virtual void update(float deltaTime) = 0;
protected:
    GameObject *_obj;
};