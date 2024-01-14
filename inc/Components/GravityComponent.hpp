#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

class GravityComponent : public Component {
public:
    GravityComponent();
    GravityComponent(GameObject *gameObject);
    void update(float deltaTime) override;
    void setGravity(float gravity);
    void setGameObject(GameObject *gameObject) override;
    void setGrounded(bool grounded);
    ~GravityComponent() override = default;
    void setStatic() override;
    bool  isGrounded;
private:
    float m_Gravity = 0.0f;
    float limitedSubstitution;
    float limitedGravity;
};
