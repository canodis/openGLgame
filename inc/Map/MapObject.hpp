#pragma once

#include "ivec2.hpp"
#include "GameObjectManager.hpp"
#include "../glm/glm.hpp"
#include "ShaderProgram.hpp"

class MapObject
{
public:
    MapObject(glm::ivec3 position, unsigned int textureId, int layer, bool isCollidable);

    std::string texturePath;
    GameObject* m_gameObject;
    bool isCollidable;
    int getLayer() { return layer; }
    unsigned int getTextureId() { return m_gameObject->GetTextureId(); }
    void setModelMatrix(glm::mat4 &modelMatrix) { this->modelMatrix = modelMatrix; }
    glm::mat4 getModelMatrix() { return modelMatrix; }
private:
    int layer;
    glm::mat4 modelMatrix;
};