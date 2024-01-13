#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

class BoxCollision2d : public Component {
public:
    void update(float deltaTime) override;
    void setGameObject(GameObject *gameObject) override;
    void isColliding(GameObject *gameObject);
};
