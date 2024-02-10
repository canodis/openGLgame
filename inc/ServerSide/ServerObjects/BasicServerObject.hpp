#pragma once

#include "ServerObject.hpp"

class BasicServerObject : public ServerObject
{
public:
    void update(float deltaTime) override;
private:
};