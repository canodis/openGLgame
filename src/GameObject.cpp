#include "GameObject.hpp"
#include "Scene.hpp"

GameObject::GameObject()
{
    transform.position = glm::vec3(0.0f);
    transform.rotation = glm::vec3(0.0f);
    transform.scale = glm::vec3(0.3f);
    color = glm::vec4(1.0f);
}

void GameObject::Draw()
{
    m_Vao->activate();
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
    m_Vao->deactivate();
}

void GameObject::SetShaderProgram(ShaderProgram *shaderProgram)
{
    m_ShaderProgram = shaderProgram;
}

GameObject::~GameObject()
{
}

void GameObject::SetColor(const glm::vec4 &color)
{
    this->color = color;
}

void GameObject::SetTexture(unsigned int textureId)
{
    this->textureId = textureId;
}

unsigned int GameObject::GetTexture() const
{
    return (textureId);
}

void GameObject::UpdateTransform()
{
    scale = glm::scale(glm::mat4(1.0f), transform.scale);
    rotation = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    translation = glm::translate(glm::mat4(1.0f), transform.position);

    m_ShaderProgram->use();
    glm::mat4 mtxTransform = Camera2D::getInstance().GetViewMatrix() * translation * rotation * scale;
    Scene::getInstance().textureManager->activateTexture(0, textureId);
    GLint textureSamplerLocation = glGetUniformLocation(m_ShaderProgram->getProgramId(), "textureSampler");
    m_ShaderProgram->setInt("textureSampler", 0);
    m_ShaderProgram->setMat4("mtxTransform", &mtxTransform);
}