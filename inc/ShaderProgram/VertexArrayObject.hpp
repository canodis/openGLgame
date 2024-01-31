#pragma once

# include <glad.h>
# include <glfw3.h>
# include "VertexTypes.hpp"

class VertexArrayObject
{
public:
    VertexArrayObject();
    ~VertexArrayObject();
    void    build(std::vector<Vertex2dObject> &vertices, const IndexList &indices);
    void    activate();
    void    deactivate();
    unsigned int getVertexCount();
    unsigned int getIndexCount();

private:
    unsigned int m_VBoid;
    unsigned int m_VAoid;
    unsigned int m_IBoid;
    unsigned int m_IndexCount;
    unsigned int m_VertexCount;

    std::vector<unsigned int> m_AtrribList;
};
