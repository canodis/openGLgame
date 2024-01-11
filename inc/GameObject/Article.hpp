#pragma once

#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/glm.hpp"

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};


class Article
{
protected:
    unsigned int textureId;

    glm::vec4 color;
    glm::mat4 scale;
    glm::mat4 rotation;
    glm::mat4 translation;
    void UpdateTransform();
    unsigned int GetTexture() const;
    Transform GetTransform() const;
public:
    Article();
    Transform transform;
    glm::vec2 velocity;
    void SetColor(const glm::vec4 &color);
    void SetTexture(unsigned int textureId);
};