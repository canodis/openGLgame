#include "Animator.hpp"
#include "Scene.hpp"
#include <filesystem>

Animator::Animator()
{
    currentAnimation = NULL;
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

Animation *Animator::loadTexturesFromDirectory(std::string animationName, std::string path, std::string file, std::string extension, float animationSpeed)
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
    animations[animationName] = animation;
    return &animations[animationName];
}

void Animator::setCurrentAnimation(std::string animationName)
{
    if (animations.find(animationName) == animations.end())
    {
        std::cout << "Animation " << animationName << " not found" << std::endl;
        return;
    }
    if (currentAnimation == &animations[animationName])
        return;
    currentAnimation = &animations[animationName];
    currentFrame = 0;
}

Animation *Animator::getAnimation(std::string animationName)
{
    if (animations.find(animationName) == animations.end())
    {
        std::cout << "Animation " << animationName << " not found" << std::endl;
        return NULL;
    }
    return &animations[animationName];
}