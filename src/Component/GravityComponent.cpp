#include "GravityComponent.hpp"

GravityComponent::GravityComponent()
{
    m_Gravity = 9.8f;
    limitedSubstitution = 1.0f;
    limitedGravity = -15.0;
    this->object = nullptr;
}

GravityComponent::GravityComponent(GameObject *gameObject) : GravityComponent()
{
    this->object = gameObject;
}

void GravityComponent::update(float deltaTime) 
{
    float jumpForce = this->object->velocity.y * deltaTime;
    if (jumpForce > 0.1f)
    {
        this->object->velocity.y -= limitedSubstitution * deltaTime;
    }
    else
    {
        this->object->velocity.y -= m_Gravity * deltaTime;
    }
    if (this->object->velocity.y < limitedGravity)
        this->object->velocity.y = limitedGravity;
    this->object->transform.position.y += this->object->velocity.y * deltaTime;
}

void GravityComponent::setGravity(float gravity)
{
    m_Gravity = gravity;
}

void GravityComponent::setGameObject(GameObject *gameObject)
{
    this->object = gameObject;
}