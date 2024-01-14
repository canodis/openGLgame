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
        elapsedTime = 0;
        currentFrame++;
        if (currentFrame >= currentAnimation->textures.size())
            currentFrame = 0;
        object->SetTexture(currentAnimation->textures[currentFrame]);
    }
}

void Animator::setGameObject(GameObject *gameObject)
{
    object = gameObject;
}

void Animator::setStatic()
{

}

void Animator::loadTexturesFromDirectory(std::string animationName, std::string path, std::string file, std::string extension, float animationSpeed)
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
}

void Animator::setCurrentAnimation(std::string animationName)
{
    if (animations.find(animationName) == animations.end())
    {
        std::cout << "Animation " << animationName << " not found" << std::endl;
        return;
    }
    currentAnimation = &animations[animationName];
}