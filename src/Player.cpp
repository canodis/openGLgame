#include "Player.hpp"
#include "Scene.hpp"
#include <iostream>
#include <BoxCollision2d.hpp>
#include "GravityComponent.hpp"

Player::Player()
{
    speed = 5.0f;
    jumpSpeed = 5.0f;
    canJump = true;
    GameObject *object = Scene::getInstance().gameObjectManager->Create2dObject("player");
    // object->SetTexture(Scene::getInstance().textureManager->loadTexture("./textures/kirmizibalik.png"));
    object->SetShaderProgram(Scene::getInstance().shaderProgram);
    object->transform.position = glm::vec3(0);
    object->AddComponent<GravityComponent>();
    object->AddComponent<BoxCollision2d>();
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
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        obj->velocity.x = -speed * deltaTime;
        obj->transform.scale.x = -1;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        obj->velocity.x = speed * deltaTime;
        obj->transform.scale.x = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        if (obj->velocity.y <= 0)
            obj->velocity.y = jumpSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        obj->transform.position.y += speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        obj->transform.position.y -= speed * deltaTime;
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
}