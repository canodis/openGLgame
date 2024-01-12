#include "GameObject.hpp"
#include "Scene.hpp"

GameObject::GameObject()
{
    transform.position = glm::vec3(0.0f);
    transform.rotation = glm::vec3(0.0f);
    transform.scale = glm::vec3(1.0f);
    color = glm::vec4(0.1f);
    update = [this](float deltaTime) { this->DynamicUpdate(deltaTime); };
    textureId = Scene::getInstance().textureManager->missingTexture;
}

GameObject::GameObject(float x, float y, std::string textureLocation) : GameObject()
{
    transform.position = glm::vec3(x, y, 0.0f);
    textureId = Scene::getInstance().textureManager->loadTexture(textureLocation);
    DynamicUpdate(0.0f);
}

void    GameObject::DynamicUpdate(float deltaTime)
{
    for (auto& component : components)
        component->update(deltaTime);
    UpdateTransform();
    UpdateShaderProgram(translation, rotation, scale, textureId);
    Draw();
}

void    GameObject::StaticUpdate()
{
    UpdateShaderProgram(translation, rotation, scale, textureId);
    Draw();
}

void    GameObject::AddComponent(Component *component)
{
    for (auto& c : components)
    {
        if (c == component)
        {
            std::cout << "Component already exists" << std::endl;
            return;
        }
    }
    component->setGameObject(this);
    components.push_back(component);
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

GameObject::~GameObject()
{
    for (auto& component : components)
        delete component;
}