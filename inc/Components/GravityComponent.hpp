#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

class GravityComponent : public Component {
public:
    GravityComponent();
    void update(float deltaTime) override;
    void setGravity(float gravity);
    void setGameObject(GameObject *gameObject) override;
    ~GravityComponent() override = default;
private:
    float m_Gravity = 0.0f;
    float limitedSubstitution;
    float limitedGravity;
};
