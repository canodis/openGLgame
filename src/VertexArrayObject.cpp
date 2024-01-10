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

void    VertexArrayObject::build(std::vector<Vertex2dObject> &vertices, const IndexList &indices)
{
    glGenVertexArrays(1, &this->m_VAoid);
	glGenBuffers(1, &this->m_VBoid);
	glGenBuffers(1, &this->m_IBoid);
    glBindVertexArray(this->m_VAoid);

	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBoid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2dObject) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2dObject), (void *)0);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2dObject), (void *)(2 * sizeof(float)));

	glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2dObject), (void *)(6 * sizeof(float)));

    glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_IBoid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
    m_AtrribList.push_back(0);
    m_AtrribList.push_back(1);
    m_AtrribList.push_back(2);
    m_IndexCount = indices.size();
    m_VertexCount = vertices.size();
}

void    VertexArrayObject::activate()
{
    glBindVertexArray(this->m_VAoid);
    for (auto next : m_AtrribList)
        glEnableVertexAttribArray(next);

}

void    VertexArrayObject::deactivate()
{
    for (auto next : m_AtrribList)
        glDisableVertexAttribArray(next);
    glBindVertexArray(0);
}

unsigned int VertexArrayObject::getVertexCount() {
    return m_VertexCount;
}

unsigned int VertexArrayObject::getIndexCount() {
    return m_IndexCount;
}