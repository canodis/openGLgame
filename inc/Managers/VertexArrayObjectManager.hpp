#pragma once

#include <map>
#include <iostream>

class VertexArrayObject;

class VertexArrayObjectManager
{
public:
    VertexArrayObjectManager();
    void addNewObject(std::string name, VertexArrayObject *vao);
    void setRectangle(VertexArrayObject *vao);
    VertexArrayObject *getVao(std::string name);
    VertexArrayObject *getRectangle() { return m_Rectangle; }
private:
    std::map<std::string, VertexArrayObject *>  m_VaoMap;
    VertexArrayObject *m_Rectangle;
};
