#include "VaoObject.hpp"
#include "Scene.hpp"


void VaoObject::SetShaderProgram(ShaderProgram *shaderProgram)
{
    m_ShaderProgram = shaderProgram;
}

void VaoObject::UpdateShaderProgram(glm::mat4 &t, glm::mat4 &r, glm::mat4 &s, glm::vec4 &color, unsigned int textureId)
{
    m_ShaderProgram->use();
    glm::mat4 mtxTransform = Camera2D::getInstance().GetViewMatrix() * t * r * s;
    Scene::getInstance().textureManager->activateTexture(0, textureId);
    m_ShaderProgram->setVec4("objColor", color);
    m_ShaderProgram->setMat4("mtxTransform", &mtxTransform);
    m_ShaderProgram->setFloat("lightInstensity", 0.3f);
    
    m_ShaderProgram->setVec2("lightPosition", glm::vec2(0,0));
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