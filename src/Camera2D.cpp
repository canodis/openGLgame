#include "../inc/Camera2D.hpp"
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
}
