#include "GameObjectManager.hpp"
#include "VertexArrayObjectManager.hpp"

GameObjectManager::GameObjectManager(VertexArrayObjectManager *vaoManager)
{
    m_VaoManager = vaoManager;
}

GameObject *GameObjectManager::Create2dObject(std::string name, const glm::vec4 &color)
{
    if (!m_VaoManager->getVao(name))
    {
        std::vector<Vertex2dObject> vertices;
        std::vector<unsigned int> indices;
        float length = 1;
        glm::vec2 verticesPos[] = {
            glm::vec2(-length / 2, -length / 2),
            glm::vec2(length / 2, -length / 2),
            glm::vec2(length / 2, length / 2),
            glm::vec2(-length / 2, length / 2)};

        glm::vec2 texCoords[] = {
            glm::vec2(0.0f, 1.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(0.0f, 0.0f)};

        Vertex2dObject tempVertices[4];
        for (int i = 0; i < 4; i++)
        {
            tempVertices[i].pos = verticesPos[i];
            tempVertices[i].color = color;
            tempVertices[i].texCoord = texCoords[i];
        }
        for (int i = 0; i < 4; i++)
            vertices.push_back(tempVertices[i]);

        indices = {0, 1, 2, 2, 3, 0};

        VertexArrayObject *vao = new VertexArrayObject();
        vao->build(vertices, indices);
        m_VaoManager->addNewObject(name, vao);
        m_VaoMap[name] = vao;
    }

    GameObject *object = new GameObject();
    object->m_Vao = m_VaoManager->getVao(name);
    object->m_IndexCount = object->m_Vao->getIndexCount();
    object->m_VertexCount = object->m_Vao->getVertexCount();
    return object;
}
