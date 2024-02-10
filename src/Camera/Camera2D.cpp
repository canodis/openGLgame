#include "Camera2D.hpp"
#include "Scene.hpp"
#include "ServerPlayer.hpp"

void Camera2D::update(GLFWwindow *window, float deltaTime)
{
    _counter += deltaTime;
    if (_counter > 0.5f)
    {
        _counter = 0;
        glfwSetWindowTitle(window, std::to_string((int)(1 / deltaTime)).c_str());
    }
}

glm::mat4 Camera2D::GetViewMatrix() const
{
    return glm::translate(glm::mat4(1.0f), -camPosition);
}

void Camera2D::setProjection(float left, float right, float bottom, float top)
{
    mtxProj = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    widthx = left - 1;
    widthy = right + 1;
    heightx = bottom - 1;
    heighty = top + 1;
}

void    Camera2D::followPoint(GLFWwindow *window, glm::vec2 point)
{
    camPosition.x = point.x;
    camPosition.y = point.y;
}

bool Camera2D::isInsideCameraView(GameObject *object)
{
    if (object->transform.position.x > camPosition.x + widthx && object->transform.position.x < camPosition.x + widthy)
        if (object->transform.position.y > camPosition.y + heightx && object->transform.position.y < camPosition.y + heighty)
            return true;
    return false;
}

void Camera2D::renderGameObjects(std::map<dis::ivec2, GameObject *> &gameObjects, float deltaTime)
{
    for (auto &gameObject : gameObjects)
    {
        if (isInsideCameraView(gameObject.second))
        {
            gameObject.second->update(deltaTime);
        }
    }
}

glm::vec3 Camera2D::getMouseWorldPosition(GLFWwindow *window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    glm::vec2 ndcPos;
    ndcPos.x = (xpos / windowWidth) * 2.0f - 1.0f;
    ndcPos.y = 1.0f - (ypos / windowHeight) * 2.0f;

    glm::vec4 clipSpacePos = glm::vec4(glm::vec3(ndcPos, -1.0f), 1.0f);
    glm::vec4 worldPos = glm::inverse(mtxProj) * clipSpacePos;
    worldPos += glm::vec4(camPosition, 0.0f);

    return glm::vec3(worldPos.x, worldPos.y, 0);
}

void Camera2D::renderMapObjects(std::map<int, std::map<dis::ivec2, MapObject *>> &objects, float delta)
{
    std::map<unsigned int, std::vector<MapObject*>> instances;
    for (auto &layer : objects)
    {
        for (auto &object : layer.second)
        {
            if (isInsideCameraView(object.second->m_gameObject))
            {
                instances[object.second->getTextureId()].push_back(object.second);
            }
        }
    }
    for (auto &instance : instances)
    {
        Scene::getInstance().textureManager->activateTexture(0, instance.first);
        for (auto &object : instance.second)
        {
            object->m_gameObject->update(delta);
        }
    }
}