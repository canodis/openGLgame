#pragma once

#include <map>
#include "GameObject.hpp"
#include "ivec2.hpp"

class BoxCollision2dController 
{
public:
    std::map<dis::ivec2, GameObject *> objects;
};
