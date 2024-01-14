#pragma once

#include "Component.hpp"
#include "Animation.hpp"
#include <map>


class Animator : public Component 
{
public:
    Animator();
    Animator(GameObject *gameObject);
    ~Animator() override;
    void update(float deltaTime) override;
    void setGameObject(GameObject *gameObject) override;
    void loadTexturesFromDirectory(std::string animationName, std::string path, std::string file, std::string extension, float animationSpeed);
    void setCurrentAnimation(std::string animationName);
    void setStatic() override;
private:
    Animation *currentAnimation;
    float elapsedTime;
    int currentFrame;
    std::map<std::string, Animation> animations;
};