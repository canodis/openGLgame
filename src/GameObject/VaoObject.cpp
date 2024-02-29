#include "VaoObject.hpp"
#include "Scene.hpp"


void VaoObject::SetShaderProgram(ShaderProgram *shaderProgram)
{
    m_ShaderProgram = shaderProgram;
}

void VaoObject::UpdateShaderProgram(glm::mat4 &t, glm::mat4 &r, glm::mat4 &s, glm::vec4 &color, unsigned int textureId)
{
    m_ShaderProgram->use();
    glm::mat4 mtxTransform = t * r * s;
    Scene::getInstance().textureManager->activateTexture(0, textureId);
    m_ShaderProgram->setVec4("objColor", color);
    m_ShaderProgram->setMat4("mtxTransform", &mtxTransform);
    const glm::mat4 projMatrix = Camera2D::getInstance().GetViewMatrix();
    m_ShaderProgram->setMat4("projMatrix", &projMatrix);
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

VaoObject::~VaoObject()
{
    delete m_Vao;
}