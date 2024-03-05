#pragma once

class GameObjectManager;
#include "GameObject.hpp"
#include <map>
#include <string>

class VertexArrayObjectManager;

class GameObjectManager
{
public:
    GameObjectManager(VertexArrayObjectManager *vaoManager);
    ~GameObjectManager();

    GameObject *Create2dObject(std::string name, const glm::vec4 &color = glm::vec4(1.0f));
    GameObject *CreateColor2dCube(std::string name, const glm::vec4 &color = glm::vec4(1.0f));
    GameObject *CreateRectangle(const glm::vec4 &color = glm::vec4(1.0f));
    GameObject *GetGameObject(const std::string &name);
    void        DestroyGameObject(const std::string &name);

    private:
        std::map<std::string, VertexArrayObject *> m_VaoMap;
        VertexArrayObject *m_Rectangle;
        VertexArrayObjectManager *m_VaoManager;
};