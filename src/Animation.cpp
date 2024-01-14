#include "Animation.hpp"

Animation::Animation()
{
    loop = true;
    animationSpeed = 0.1f;
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

