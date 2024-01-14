#include "Player.hpp"
#include "Scene.hpp"
#include <iostream>
#include <BoxCollision2d.hpp>
#include "GravityComponent.hpp"
#include "Animator.hpp"

Player::Player()
{
    speed = 5.0f;
    jumpSpeed = 5.0f;
    canJump = true;
    GameObject *object = Scene::getInstance().gameObjectManager->Create2dObject("player");
    object->SetShaderProgram(Scene::getInstance().shaderProgram);
    object->transform.position = glm::vec3(0);
    object->AddComponent<GravityComponent>();
    object->AddComponent<BoxCollision2d>()->setCollisionScale(glm::vec2(0.8f, 0.9f));
    Animator *anim = object->AddComponent<Animator>();
    anim->loadTexturesFromDirectory("idle", "./animations/Player/Idle/", "PlayerIdle", "png", 0.2f);
    anim->loadTexturesFromDirectory("run", "./animations/Player/Run/", "PlayerRun", "png", 0.1f);
    anim->loadTexturesFromDirectory("jump", "./animations/Player/Jump/", "PlayerJump", "png", 0.1f)->loop = false;
    anim->loadTexturesFromDirectory("fall", "./animations/Player/Fall/", "PlayerFall", "png", 0.1f);
    anim->setCurrentAnimation("idle");
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
        if (obj->GetComponent<GravityComponent>()->isGrounded)
        {
            obj->GetComponent<GravityComponent>()->setGrounded(false);
            obj->velocity.y = jumpSpeed;
        }
    }
}

void    Player::Update(float deltaTime)
{
    obj->transform.position.x += obj->velocity.x;

    Animator *anim = obj->GetComponent<Animator>();

    if (obj->velocity.y > 0)
    {
        anim->setCurrentAnimation("jump");
    }
    else if (obj->velocity.y < 0)
    {
        anim->setCurrentAnimation("fall");
    }
    else if (obj->velocity.x != 0)
    {
        anim->setCurrentAnimation("run");
    }
    else
    {
        anim->setCurrentAnimation("idle");
    }
    
}
