#pragma once

#include "GameObject.hpp"

class Player
{
public:
    Player();
    ~Player();
    void setGameObject(GameObject *gameObject);
    void processInput(GLFWwindow &window, float deltaTime);
    void update(const float &deltaTime);
    void ResetVelocityX() { obj->velocity.x = 0.0f; }
    void ResetVelocityY() { obj->velocity.y = 0.0f; }
    void ResetVelocity() { obj->velocity = glm::vec2(0.0f); }

    void SetTargetPosition(const glm::vec3 &target) { targetPosition = target; }
    void SetTargetPosition(const float &x, const float &y) { targetPosition = glm::vec3(x, y, 0); }
    void SetPosition(const glm::vec3 &position) { obj->transform.position = position; }
    void SetPosition(const float &x, const float &y) { obj->transform.position = glm::vec3(x, y, 0); }

    glm::vec2 GetPosition() const { return (obj->GetPosition()); }
    glm::vec2 GetVelocity() const { return (obj->velocity); }
    Transform GetTransform() const { return (obj->transform); }
    glm::vec2 GetTargetPosition() const { return (targetPosition); }
    void move(float deltaTime);
private:
    GameObject *obj;
    float speed;
    float jumpSpeed;
    bool canJump;
    glm::vec3 targetPosition;
    bool lastMouseRightButtonState = true;
    const float EPSILON = 0.1f;
    glm::vec2 lastDirection;
};
