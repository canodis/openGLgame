#pragma once

class ThrowObject;
#include "GameObject.hpp"
#include "../glm/glm.hpp"

class ThrowObject
{
public:
    ThrowObject();
    ThrowObject(int id, const glm::vec3 &direction, const GameObject &obj);
    ThrowObject(const glm::vec3 &targetPosition, const GameObject &obj, float &lifeTime, const glm::vec3 &direction);
    bool update(float deltaTime);
    int id;
    GameObject *obj;
private:
    float counter;
    float speed;
    float lifeTime;
    glm::vec3 direction;
    glm::vec3 targetPosition;

    void calculateRotation();
};