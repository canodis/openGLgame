#pragma once

#include "GameObject.hpp"

class Player
{
public:
    Player();
    ~Player();
    void setGameObject(GameObject *gameObject);
    void processInput(GLFWwindow *window, float deltaTime);
    glm::vec2 velocity;
    GameObject *obj;
    float speed;
private:
};