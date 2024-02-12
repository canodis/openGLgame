#include "VertexArrayObject.hpp"

VertexArrayObject::VertexArrayObject()
{
    m_VAoid = 0;
    m_IBoid = 0;
    m_VBoid = 0;
}

VertexArrayObject::~VertexArrayObject()
{
    if (m_VAoid)
        glDeleteBuffers(1, &m_VAoid);
    if (m_VBoid)
        glDeleteBuffers(1, &m_VBoid);
    if (m_IBoid)
        glDeleteBuffers(1, &m_IBoid);
}

void VertexArrayObject::build(std::vector<Vertex2dObject> &vertices, const IndexList &indices)
{
    glGenVertexArrays(1, &this->m_VAoid);
    glGenBuffers(1, &this->m_VBoid);
    glGenBuffers(1, &this->m_IBoid);
    glBindVertexArray(this->m_VAoid);

    glBindBuffer(GL_ARRAY_BUFFER, this->m_VBoid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2dObject) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2dObject), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2dObject), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_IBoid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

    m_AtrribList.push_back(0);
    m_AtrribList.push_back(1);
    m_IndexCount = indices.size();
    m_VertexCount = vertices.size();
}

void VertexArrayObject::buildInstanced(std::vector<Vertex2dObject> &vertices, const IndexList &indices)
{
    glGenVertexArrays(1, &this->m_VAoid);
    glGenBuffers(1, &this->m_VBoid);
    glGenBuffers(1, &this->m_IBoid);
    glBindVertexArray(this->m_VAoid);

    glBindBuffer(GL_ARRAY_BUFFER, this->m_VBoid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2dObject) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2dObject), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2dObject), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_IBoid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

    m_AtrribList.push_back(0);
    m_AtrribList.push_back(1);
    m_IndexCount = indices.size();
    m_VertexCount = vertices.size();

    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * instanceMatrices.size(), instanceMatrices.data(), GL_STATIC_DRAW);

    for (size_t i = 0; i < 4; i++)
    {
        glEnableVertexAttribArray(2 + i);
        glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4) * i));
        glVertexAttribDivisor(2 + i, 1);
    }
}

void VertexArrayObject::activate()
{
    glBindVertexArray(this->m_VAoid);
    for (auto next : m_AtrribList)
        glEnableVertexAttribArray(next);
}

void VertexArrayObject::deactivate()
{
    for (auto next : m_AtrribList)
        glDisableVertexAttribArray(next);
    glBindVertexArray(0);
}

unsigned int VertexArrayObject::getVertexCount()
{
    return m_VertexCount;
}

unsigned int VertexArrayObject::getIndexCount()
{
    return m_IndexCount;
}