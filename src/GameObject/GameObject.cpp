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
    for (auto& component : components)
        component->update(0.0f);
    UpdateShaderProgram(translation, rotation, scale, color,textureId);
    Draw();
}

void    GameObject::setStatic()
{
    isStatic = true;
    update = [this](float deltaTime) { this->StaticUpdate(); };
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

GameObject::~GameObject()
{
    for (auto& component : components)
        delete component;
}