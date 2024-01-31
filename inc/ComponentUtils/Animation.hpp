#pragma once

#include <vector>

class Animation
{
public:
    Animation();
    Animation(float speed);
    ~Animation();
    void addTexture(unsigned int texture);
    float animationSpeed;
    std::vector<unsigned int> textures;
    bool loop;
private:
};