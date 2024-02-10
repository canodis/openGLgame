#include "GameObject.hpp"
#include "Scene.hpp"

GameObject::GameObject()
{
    transform.position = glm::vec3(0.0f);
    transform.rotation = glm::vec3(0.0f);
    transform.scale = glm::vec3(1.0f);
    color = glm::vec4(1.0f);
    update = [this](float deltaTime) { this->DynamicUpdate(deltaTime); };
    textureId = Scene::getInstance().textureManager->missingTexture;
}

GameObject::GameObject(float x, float y, std::string textureLocation) : GameObject()
{
    transform.position = glm::vec3(x, y, 0.0f);
    textureId = Scene::getInstance().textureManager->loadTexture(textureLocation);
}

void    GameObject::DynamicUpdate(float deltaTime)
{
    for (auto& component : components)
        component->update(deltaTime);
    UpdateTransform();
    UpdateShaderProgram(translation, rotation, scale, color, textureId);
    Draw();
}

void    GameObject::StaticUpdate()
{
    auto startCalculate = std::chrono::high_resolution_clock::now();

    for (auto& component : components)
        component->update(0.0f);
    UpdateShaderProgram(translation, rotation, scale, color,textureId);
    //end calculate
    auto endCalculate = std::chrono::high_resolution_clock::now();
    Scene::getInstance().calculeTotalTime += std::chrono::duration_cast<std::chrono::microseconds>(endCalculate - startCalculate).count();
    auto startDraw = std::chrono::high_resolution_clock::now();
    Draw();
    auto endDraw = std::chrono::high_resolution_clock::now();
    Scene::getInstance().drawTotalTime += std::chrono::duration_cast<std::chrono::microseconds>(endDraw - startDraw).count();
}

void    GameObject::setStatic()
{
    isStatic = true;
    DynamicUpdate(0);
    update = [this](float deltaTime) { this->StaticUpdate(); };
    for (auto& component : components)
        component->setStatic();
}

void    GameObject::RemoveComponent(Component *component)
{
    for (auto it = components.begin(); it != components.end(); it++)
    {
        if (*it == component)
        {
            components.erase(it);
            break;
        }
    }
}

void    GameObject::setPosition(glm::vec3 position)
{
    transform.position = position;
    UpdateTransform();
}

void    GameObject::move(glm::vec3 target, float deltaTime, float speed)
{
    if (glm::distance(transform.position, target) < 0.1f)
        return;
    glm::vec2 direction = target - transform.position;
    direction = glm::normalize(direction);
    velocity = direction * speed;
    transform.position += glm::vec3(velocity * deltaTime, 0.0f);
    transform.scale.x = direction.x > 0 ? 1 : -1;
}

GameObject::~GameObject()
{
    for (auto& component : components)
        delete component;
}