#include "VaoObject.hpp"
#include "Scene.hpp"

void VaoObject::SetShaderProgram(ShaderProgram *shaderProgram)
{
    m_ShaderProgram = shaderProgram;
}

void VaoObject::UpdateShaderProgram(glm::mat4 &t, glm::mat4 &r, glm::mat4 &s, unsigned int textureId)
{
    m_ShaderProgram->use();
    glm::mat4 mtxTransform = Camera2D::getInstance().GetViewMatrix() * t * r * s;
    Scene::getInstance().textureManager->activateTexture(0, textureId);
    GLint textureSamplerLocation = glGetUniformLocation(m_ShaderProgram->getProgramId(), "textureSampler");
    m_ShaderProgram->setInt("textureSampler", 0);
    m_ShaderProgram->setMat4("mtxTransform", &mtxTransform);
}

void VaoObject::Draw()
{
    m_Vao->activate();
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
    m_Vao->deactivate();
}

VaoObject::VaoObject()
{
    m_ShaderProgram = Scene::getInstance().shaderProgram;
}