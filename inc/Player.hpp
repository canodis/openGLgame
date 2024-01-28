#pragma once

#include "GameObject.hpp"

class Player
{
public:
    Player();
    ~Player();
    void setGameObject(GameObject *gameObject);
    void processInput(GLFWwindow *window, float deltaTime);
    void Update(float deltaTime);
    void ResetVelocityX() { obj->velocity.x = 0.0f; }
    void ResetVelocityY() { obj->velocity.y = 0.0f; }
    void ResetVelocity() { obj->velocity = glm::vec2(0.0f); }

    glm::vec2 GetPosition() const { return (obj->GetPosition()); }
    glm::vec2 GetVelocity() const { return (obj->velocity); }
private:
    GameObject *obj;
    float speed;
    float jumpSpeed;
    bool canJump;
};
