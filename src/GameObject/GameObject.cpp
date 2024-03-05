#include "GameObject.hpp"
#include "Scene.hpp"

GameObject::GameObject()
{
    transform.position = glm::vec3(0.0f);
    transform.rotation = glm::vec3(0.0f);
    transform.scale = glm::vec3(1.0f);
    color = glm::vec4(1.0f);
    update = [this](float deltaTime)
    { this->DynamicUpdate(deltaTime); };
    textureId = Scene::getInstance().textureManager->missingTexture;
}

GameObject::GameObject(GameObject *gameObject) : GameObject()
{
    transform.position = gameObject->transform.position;
    transform.rotation = gameObject->transform.rotation;
    transform.scale = gameObject->transform.scale;
    color = gameObject->color;
    textureId = gameObject->textureId;
    m_Vao = gameObject->m_Vao;
    m_IndexCount = gameObject->m_IndexCount;
    m_VertexCount = gameObject->m_VertexCount;
    m_ShaderProgram = gameObject->m_ShaderProgram;
}

GameObject::GameObject(float x, float y, std::string textureLocation) : GameObject()
{
    transform.position = glm::vec3(x, y, 0.0f);
    textureId = Scene::getInstance().textureManager->loadTexture(textureLocation);
}

void GameObject::DynamicUpdate(float deltaTime)
{
    for (auto &component : components)
        component->update(deltaTime);
    UpdateTransform();
    UpdateShaderProgram(translation, rotation, scale, color, textureId);
    Draw();
}

void GameObject::StaticUpdate()
{
    for (auto &component : components)
        component->update(0.0f);
    UpdateShaderProgram(translation, rotation, scale, color, textureId);
    Draw();
}

void GameObject::setStatic()
{
    isStatic = true;
    DynamicUpdate(0);
    update = [this](float deltaTime)
    { this->StaticUpdate(); };
    for (auto &component : components)
        component->setStatic();
}

void GameObject::RemoveComponent(Component *component)
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

void GameObject::setPosition(glm::vec3 position)
{
    transform.position = position;
    UpdateTransform();
}

void GameObject::move(const glm::vec3 &target, float deltaTime, float speed)
{
    if (glm::distance(transform.position, target) < 0.1f)
        return;
    glm::vec2 direction = target - transform.position;
    direction = glm::normalize(direction);
    velocity = direction * speed;
    transform.position += glm::vec3(velocity * deltaTime, 0.0f);
    transform.scale.x = direction.x > 0 ? 1 : -1;
}

void GameObject::moveToInfinite(const glm::vec2 &direction, float deltaTime, float speed)
{
    transform.position += glm::vec3(direction * speed * deltaTime, 0.0f);
}



GameObject::~GameObject()
{
    for (auto &component : components)
        delete component;
    
}

glm::vec3 GameObject::GetPosition() const
{
    return (transform.position);
}
glm::vec3 GameObject::GetScale() const
{
    return (transform.scale);
}
glm::vec3 GameObject::GetRotation() const
{
    return (transform.rotation);
}