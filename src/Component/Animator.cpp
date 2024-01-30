#include "Animator.hpp"
#include "Scene.hpp"
#include <filesystem>

Animator::Animator()
{
    currentAnimation = NULL;
    elapsedTime = 0;
    currentFrame = 0;
}

Animator::Animator(GameObject *gameObject) : Animator()
{
    object = gameObject;
}

Animator::~Animator()
{
}

void Animator::update(float deltaTime)
{
    if (currentAnimation == NULL)
        return;
    elapsedTime += deltaTime;
    if (elapsedTime >= currentAnimation->animationSpeed)
    {
        if (currentAnimation->loop == false && currentFrame == currentAnimation->textures.size())
        {
            return;
        }
        if (currentFrame >= currentAnimation->textures.size())
        {
            currentFrame = 0;
        }
        object->SetTexture(currentAnimation->textures[currentFrame]);
        elapsedTime = 0;
        currentFrame++;
    }
}

void Animator::setGameObject(GameObject *gameObject)
{
    object = gameObject;
}

void Animator::setStatic()
{
}

Animation *Animator::loadTexturesFromDirectory(AnimationType anim, std::string path, std::string file, std::string extension, float animationSpeed)
{
    std::string fullPath;
    Animation animation;

    int i = 0;
    while (true)
    {
        fullPath = path + file + std::to_string(i) + "." + extension;
        if (!std::__fs::filesystem::exists(fullPath))
        {
            break;
        }
        unsigned int texture = Scene::getInstance().textureManager->loadTexture(fullPath.c_str());
        animation.addTexture(texture);
        animation.animationSpeed = animationSpeed;
        i++;
    }
    animations[anim] = animation;
    return &animations[anim];
}

void Animator::setCurrentAnimation(int animationState)
{
    if (animations.find(animationState) == animations.end())
    {
        std::cout << "Animation " << animationState << " not found" << std::endl;
        return;
    }
    if (currentAnimation == &animations[animationState])
        return;
    currentAnimation = &animations[animationState];
    currentAnimationType = (int)animationState;
    currentFrame = 0;
    elapsedTime = 0;
}

Animation *Animator::getAnimation(AnimationType animationType)
{
    if (animations.find(animationType) == animations.end())
    {
        std::cout << "Animation " << animationType << " not found" << std::endl;
        return NULL;
    }
    return &animations[animationType];
}

int Animator::getAnimationType() const
{
    return currentAnimationType;
}
