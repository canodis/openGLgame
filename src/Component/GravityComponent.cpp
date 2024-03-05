#include "GravityComponent.hpp"

GravityComponent::GravityComponent()
{
    isGrounded = false;
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
    if (isGrounded)
    {
        this->object->velocity.y = 0;
        return;
    }
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

void GravityComponent::setGrounded(bool grounded)
{
    isGrounded = grounded;
}

void GravityComponent::setStatic()
{
}