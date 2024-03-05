#include "MapObject.hpp"
#include "Scene.hpp"

MapObject::MapObject(glm::ivec3 position, unsigned int textureId, int layer, bool isCollidable)
{
    m_gameObject = Scene::getInstance().gameObjectManager->CreateRectangle();
    m_gameObject->transform.position = position;
    m_gameObject->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
    m_gameObject->SetTexture(textureId);
    this->layer = layer;
    this->isCollidable = isCollidable;
}
