#include "Player.hpp"
#include "Scene.hpp"
#include <iostream>

Player::Player()
{
    speed = 1.0f;
    GameObject *object = Scene::getInstance().gameObjectManager->Create2dObject("player", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    object->SetTexture(Scene::getInstance().textureManager->loadTexture("./textures/kirmizibalik.png"));
    object->SetShaderProgram(Scene::getInstance().shaderProgram);
    Scene::getInstance().gameObjects.push_back(object);
    this->setGameObject(object);
}

Player::~Player()
{
}

void Player::setGameObject(GameObject *gameObject)
{
    obj = gameObject;
}

void Player::processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        obj->velocity.y += speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        obj->velocity.y = -speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        obj->velocity.x = -speed * deltaTime;
        obj->transform.scale.x = -1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        obj->velocity.x = speed * deltaTime;
        obj->transform.scale.x = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        obj->transform.rotation.z += speed * deltaTime * 100;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        obj->transform.rotation.z -= speed * deltaTime * 100;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        obj->transform.scale.x += speed * deltaTime;
        obj->transform.scale.y += speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        obj->transform.scale.x -= speed * deltaTime;
        obj->transform.scale.y -= speed * deltaTime;
    }
}

void    Player::Update(float deltaTime)
{
    obj->transform.position.x += obj->velocity.x;
    obj->transform.position.y += obj->velocity.y;
    obj->velocity.x = 0;
    obj->velocity.y = 0;
}