#include "Player.hpp"
#include "Scene.hpp"
#include <iostream>
#include <BoxCollision2d.hpp>
#include "GravityComponent.hpp"
#include "AnimationTypes.hpp"
#include "Animator.hpp"
#include "Client.hpp"

Player::Player() : speed(3), jumpSpeed(5)
{
    GameObject *object = Scene::getInstance().gameObjectManager->Create2dObject("player");
    object->SetTexture(Scene::getInstance().textureManager->loadTexture("./animations/Player/Idle/PlayerIdle0.png"));
    object->SetShaderProgram(Scene::getInstance().shaderProgram);
    object->transform.position = glm::vec3(0);
    object->AddComponent<BoxCollision2d>()->setCollisionScale(glm::vec2(0.8f, 0.9f));
    Animator *anim = object->AddComponent<Animator>();
    anim->loadTexturesFromDirectory(AnimationType::idle, "./animations/Player/Idle/", "PlayerIdle", "png", 0.2f);
    anim->loadTexturesFromDirectory(AnimationType::run, "./animations/Player/Run/", "PlayerRun", "png", 0.1f);
    anim->setCurrentAnimation(AnimationType::idle);
    Scene::getInstance().gameObjects.push_back(object);
    object->setPosition(glm::vec3(0, 0, 0));
    this->setGameObject(object);
    this->targetPosition = object->transform.position;
}

Player::~Player() {}

void Player::setGameObject(GameObject *gameObject)
{
    obj = gameObject;
}

void Player::processInput(GLFWwindow *window, float deltaTime)
{
    bool currentMouseRightButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE;
    if (currentMouseRightButtonState && !lastMouseRightButtonState)
    {
        targetPosition = Camera2D::getInstance().getMouseWorldPosition(window);
        Client::getInstance().udpConnection->sendPlayerAllData(obj->transform, targetPosition.x, targetPosition.y,
             deltaTime, true);
    }
    lastMouseRightButtonState = currentMouseRightButtonState;
}

void Player::Update(float deltaTime)
{
    move(deltaTime);

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

void Player::move(float deltaTime)
{
    obj->move(targetPosition, deltaTime, speed);
}
