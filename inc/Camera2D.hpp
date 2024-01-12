#pragma once

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
# define BEGINX 0.0f
# define BEGINY 0.0f

class GLFWwindow;

class Camera2D
{
public:
    static Camera2D& getInstance()
    {
        static Camera2D instance;
        return instance;
    }

    Camera2D(Camera2D const&) = delete;
    void operator=(Camera2D const&) = delete;

    void Update(GLFWwindow *window);
    void followPoint(GLFWwindow *window, glm::vec2 point);
    glm::mat4 GetViewMatrix() const;
    void SetProjection(float left, float right, float bottom, float top);
    glm::vec3 camPosition;
    glm::mat4 mtxProj;

private:
    Camera2D() : camPosition(0.0f, 0.0f, 0.0f), mtxProj(1.0f) {}
};

