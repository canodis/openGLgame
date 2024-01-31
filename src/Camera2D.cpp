#include "Camera2D.hpp"
#include "Scene.hpp"

void Camera2D::Update(GLFWwindow *window)
{
}

glm::mat4 Camera2D::GetViewMatrix() const
{
    return glm::translate(glm::mat4(1.0f), -camPosition);
}

void Camera2D::SetProjection(float left, float right, float bottom, float top)
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
            gameObject.second->update(deltaTime);
    }
}

glm::vec2 Camera2D::getMouseWorldPosition(GLFWwindow *window)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glm::vec2 mousePos = glm::vec2(xpos, ypos);
    glm::vec2 worldPos = glm::vec2(0.0f, 0.0f);
    worldPos.x = (mousePos.x - (Scene::getInstance().windowWidth / 2)) / (Scene::getInstance().windowWidth / 2);
    worldPos.y = (mousePos.y - (Scene::getInstance().windowHeight / 2)) / (Scene::getInstance().windowHeight / 2);
    worldPos = glm::vec2(camPosition.x + worldPos.x, camPosition.y + worldPos.y);
    return worldPos;
}