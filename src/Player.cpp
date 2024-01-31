#include "Player.hpp"
#include "Scene.hpp"
#include <iostream>
#include <BoxCollision2d.hpp>
#include "GravityComponent.hpp"
#include "UdpPositionSender.hpp"

Player::Player() : speed(2), jumpSpeed(5)
{
    GameObject *object = Scene::getInstance().gameObjectManager->Create2dObject("player");
    object->SetTexture(Scene::getInstance().textureManager->loadTexture("./animations/Player/Idle/PlayerIdle0.png"));
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
    }
    lastMouseRightButtonState = currentMouseRightButtonState;
}

void Player::Update(float deltaTime)
{
    if (isVectorEqual(obj->transform.position, targetPosition) == false)
    {
        move(deltaTime);
    }

    if (isVectorEqual(obj->transform.position, targetPosition) == false)
    {
        move(deltaTime);
    }

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

bool Player::isVectorEqual(glm::vec2 a, glm::vec2 b) const
{
    return (fabs(a.x - b.x) < EPSILON && fabs(a.y - b.y) < EPSILON);
}

void Player::move(float deltaTime)
{
    glm::vec2 direction = targetPosition - obj->transform.position;
    direction = glm::normalize(direction);
    obj->velocity = direction * speed;
    obj->transform.position += glm::vec3(obj->velocity * deltaTime, 0.0f);
    obj->transform.scale.x = direction.x > 0 ? 1 : -1;
}
