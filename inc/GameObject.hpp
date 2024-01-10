#pragma once

class GameObject;

#include "../glm/glm.hpp"
#include "VertexArrayObject.hpp"
#include "ShaderProgram.hpp"
#include "../glm/gtc/matrix_transform.hpp"

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

class GameObject
{
public:
    Transform transform;
    glm::vec4 color;
    VertexArrayObject   *m_Vao;
    unsigned int m_IndexCount;
    unsigned int m_VertexCount;
    ShaderProgram *m_ShaderProgram;

    glm::mat4 scale;
    glm::mat4 rotation;
    glm::mat4 translation;

    void UpdateTransform();
    void Draw();
    void SetColor(const glm::vec4 &color);
    void SetShaderProgram(ShaderProgram *shaderProgram);
    void SetTexture(unsigned int textureId);
    unsigned int GetTexture() const;
    GameObject();
    ~GameObject();
private:
    unsigned int textureId;
};