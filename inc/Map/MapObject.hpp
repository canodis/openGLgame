#pragma once

#include "ivec2.hpp"
#include "GameObjectManager.hpp"
#include "../glm/glm.hpp"

class MapObject
{
public:
    MapObject(glm::ivec3 position, unsigned int textureId, int layer, bool isCollidable);
    std::string texturePath;
    GameObject* m_gameObject;
    bool isCollidable;
    int getLayer() { return layer; }
private:
    int layer;
};