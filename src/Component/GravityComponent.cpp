#include "GravityComponent.hpp"

GravityComponent::GravityComponent()
{
    m_Gravity = 0.001f;
    this->object = nullptr;
}

void GravityComponent::update(float deltaTime) 
{
    this->object->velocity.y -= m_Gravity * deltaTime;
}

void GravityComponent::setGravity(float gravity)
{
    m_Gravity = gravity;
}

void GravityComponent::setGameObject(GameObject *gameObject)
{
    this->object = gameObject;
}