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
    width = (right - left) + 1;
    height = (top - bottom) + 1;
}

void    Camera2D::followPoint(GLFWwindow *window, glm::vec2 point)
{
    camPosition.x = point.x;
    camPosition.y = point.y;
}

void Camera2D::renderGameObjects(std::vector<GameObject *> &gameObjects, float deltaTime)
{
    for (auto &gameObject : gameObjects)
    {
        if (isInsideCameraView(gameObject))
            gameObject->update(deltaTime);
    }
}

bool Camera2D::isInsideCameraView(GameObject *object)
{
    if (object->transform.position.x > camPosition.x - width / 2 && object->transform.position.x < camPosition.x + width / 2)
    {
        if (object->transform.position.y > camPosition.y - height / 2 && object->transform.position.y < camPosition.y + height / 2)
            return true;
    }
    return false;
}