#pragma once

class GameObject;

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "VaoObject.hpp"
#include "Article.hpp"
#include "Component.hpp"

class GameObject : public Article, public VaoObject
{
public:
    GameObject();
    GameObject(float x, float y, std::string textureLocation);
    void Update(float deltaTime);
    void AddComponent(Component *component);
    Component *GetComponent(std::string name);
    void RemoveComponent(Component *component);
    ~GameObject();
    std::vector<Component*> components;
    template <typename T>
    T *GetComponent()
    {
        for (auto& component : components)
        {
            if (dynamic_cast<T*>(component))
                return (dynamic_cast<T*>(component));
        }
        std::cout << "Component not found" << std::endl;
        return (nullptr);
    }
};