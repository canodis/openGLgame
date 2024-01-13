#pragma once

#include "VertexArrayObject.hpp"
#include "ShaderProgram.hpp"

class VaoObject
{
public:
    VertexArrayObject   *m_Vao;
    unsigned int m_IndexCount;
    unsigned int m_VertexCount;
    ShaderProgram *m_ShaderProgram;

    VaoObject();
    ~VaoObject();
    void SetShaderProgram(ShaderProgram *shaderProgram);
    void UpdateShaderProgram(glm::mat4 &t, glm::mat4 &r, glm::mat4 &s, unsigned int textureId);
    void Draw();
};