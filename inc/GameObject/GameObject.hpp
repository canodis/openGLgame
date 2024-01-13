#pragma once

class GameObject;

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "VaoObject.hpp"
#include "Article.hpp"
#include "Component.hpp"
#include <functional>

class GameObject : public Article, public VaoObject
{
public:
    GameObject();
    GameObject(float x, float y, std::string textureLocation);
    ~GameObject();
    std::function<void(float)> update;
    
    void RemoveComponent(Component *component);
    std::vector<Component*> components;

    glm::vec2 GetPosition() const { return (transform.position); }
    glm::vec3 GetScale() const { return (transform.scale); }
    glm::vec3 GetRotation() const { return (transform.rotation); }

    void setPosition(glm::vec3 position);
    void setStatic();

    bool isStatic = false;


    template <typename T>
    T *AddComponent()
    {
        T *component;
        try
        {
            component = new T(this);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: Component can't created !" << std::endl;
            return (nullptr);
        }
        for (auto& component : components)
        {
            if (dynamic_cast<T*>(component))
            {
                std::cout << "Component already exist" << std::endl;
                return (nullptr);
            }
        }
        components.push_back(component);
        return (component);
    }
    
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
private:
    void DynamicUpdate(float deltaTime);
    void StaticUpdate();
};