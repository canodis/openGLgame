#include "Player.hpp"
#include "Scene.hpp"
#include <iostream>
#include <BoxCollision2d.hpp>
#include "GravityComponent.hpp"
#include "UdpPositionSender.hpp"

Player::Player() : speed(5), jumpSpeed(5)
{
    GameObject *object = Scene::getInstance().gameObjectManager->Create2dObject("player");
    object->SetShaderProgram(Scene::getInstance().shaderProgram);
    object->transform.position = glm::vec3(0);
    object->AddComponent<BoxCollision2d>()->setCollisionScale(glm::vec2(0.8f, 0.9f));
    object->AddComponent<UdpPositionSender>();
    Animator *anim = object->AddComponent<Animator>();
    anim->loadTexturesFromDirectory(AnimationType::idle, "./animations/Player/Idle/", "PlayerIdle", "png", 0.2f);
    anim->loadTexturesFromDirectory(AnimationType::run, "./animations/Player/Run/", "PlayerRun", "png", 0.1f);
    anim->setCurrentAnimation(AnimationType::idle);
    Scene::getInstance().gameObjects.push_back(object);
    object->setPosition(glm::vec3(-27, -7, 0));
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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        obj->velocity.y = speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        obj->velocity.y = -speed * deltaTime;
    }

}

void    Player::Update(float deltaTime)
{
    obj->transform.position.x += obj->velocity.x;
    obj->transform.position.y += obj->velocity.y;

    Animator *anim = obj->GetComponent<Animator>();

    if (obj->velocity.x != 0 || obj->velocity.y != 0)
    {
        anim->setCurrentAnimation(AnimationType::run);
    }
    else
    {
        anim->setCurrentAnimation(AnimationType::idle);
    }
    
}
