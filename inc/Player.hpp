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
    GameObject *obj;
    float speed;
};
