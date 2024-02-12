#include "BasicNpc.hpp"

void BasicNpc::update(float deltaTime)
{
    obj->move(glm::vec3(targetPosition.x, targetPosition.y, 0), deltaTime, speed);

    Animator *anim = obj->GetComponent<Animator>();

    if (obj->velocity.x != 0 || obj->velocity.y != 0)
    {
        anim->setCurrentAnimation(AnimationType::run);
    }
    else
    {
        anim->setCurrentAnimation(AnimationType::idle);
    }
    obj->velocity.x = 0;
    obj->velocity.y = 0;
}

BasicNpc::BasicNpc() { }