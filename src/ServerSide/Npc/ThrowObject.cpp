#include "ThrowObject.hpp"
#include "Scene.hpp"

ThrowObject::ThrowObject()
{
    lifeTime = 5.0f;
    speed = 5.0f;
    counter = 0.0f;
    this->obj = Scene::getInstance().gameObjectManager->CreateRectangle();
}

ThrowObject::ThrowObject(int id, const glm::vec3 &direction, const GameObject &obj) : ThrowObject()
{
    this->direction = direction;
    this->obj->SetTexture(obj.GetTextureId());
    this->id = id;
    calculateRotation();
}

ThrowObject::ThrowObject(const glm::vec3 &targetPosition, const GameObject &obj, float &lifeTime, const glm::vec3 &direction): ThrowObject()
{
    this->targetPosition = targetPosition;
    this->obj->SetTexture(obj.GetTextureId());
    this->lifeTime = lifeTime;
    this->direction = direction;
    calculateRotation();
}

bool ThrowObject::update(float deltaTime)
{
    counter += deltaTime;
    obj->update(deltaTime);
    if (counter > lifeTime)
    {
        return false;
    }
    obj->moveToInfinite(direction, deltaTime, speed);
    return true;
}

void ThrowObject::calculateRotation()
{
    float angle = atan2(direction.y, direction.x) * 57.2958f;
    obj->transform.rotation = glm::vec3(0, 0, angle);
}
