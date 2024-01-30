#pragma once

class Animator;

#include "Component.hpp"
#include "Animation.hpp"
#include "AnimationTypes.hpp"
#include <map>


class Animator : public Component 
{
public:
    Animator();
    Animator(bool isServerPlayer);
    Animator(GameObject *gameObject);
    ~Animator() override;
    void update(float deltaTime) override;
    void setGameObject(GameObject *gameObject) override;
    Animation *loadTexturesFromDirectory(AnimationType anim, std::string path, std::string file, std::string extension, float animationSpeed);
    void setCurrentAnimation(AnimationType animationState);
    void setStatic() override;
    Animation *getAnimation(AnimationType animationType);
    void setServerPlayer(bool isServerPlayer);
    void sendAnimationToServer(AnimationType animationType);
private:
    bool isServerPlayer;
    Animation *currentAnimation;
    AnimationType currentAnimationType;
    float elapsedTime;
    int currentFrame;
    std::map<AnimationType, Animation> animations;
};