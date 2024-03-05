#include "Article.hpp"

Article::Article()
{
    velocity = glm::vec2(0.0f, 0.0f);
    transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
    color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
}

Transform Article::GetTransform() const
{
    return (transform);
}

void Article::SetColor(const glm::vec4 &color)
{
    this->color = color;
}

#include <iostream>

void Article::SetTexture(unsigned int textureId)
{
    this->textureId = textureId;
}

unsigned int Article::GetTextureId() const
{
    return (textureId);
}

void Article::UpdateTransform()
{
    scale = glm::scale(glm::mat4(1.0f), transform.scale);
    rotation = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::mat4(1.0f), transform.position);
}

glm::mat4 Article::calculateModelMatrix()
{
    UpdateTransform();
    glm::mat4 model = translation * rotation * scale;
    return model;
}