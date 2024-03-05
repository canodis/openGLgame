#pragma once

#include "Component.hpp"
#include "ivec2.hpp"
#include <vector>

class BoxCollision2d : public Component {
public:
    BoxCollision2d();
    BoxCollision2d(GameObject *gameObject);
    ~BoxCollision2d() override;
    void update(float deltaTime) override;
    void dynamicUpdate(float deltaTime);
    void staticUpdate(float deltaTime);
    void isColliding(GameObject &gameObject);
    void setCollisionScale(glm::vec2 scale);
    dis::ivec2 getOrigin(GameObject &gameObject);
    void setStatic() override;
private:
    void drawDebugCollision();
    void overlapCalculation(GameObject &other, float &overlapX, float &overlapY);

    std::vector<GameObject *> debugObjects;

    dis::ivec2 left;
    dis::ivec2 right;
    dis::ivec2 up;
    dis::ivec2 down;
    dis::ivec2 leftup;
    dis::ivec2 leftdown;
    dis::ivec2 rightup;
    dis::ivec2 rightdown;

    glm::vec2 collisionScale;
    dis::ivec2 objorigin;

    std::function<void(float)> updateType;
};
