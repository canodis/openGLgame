#include "Animation.hpp"

Animation::Animation()
{
}

Animation::Animation(float speed)
{
    animationSpeed = speed;
}

Animation::~Animation()
{
}

void    Animation::addTexture(unsigned int texture)
{
    textures.push_back(texture);
}

