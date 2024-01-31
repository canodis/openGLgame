#pragma once

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "GameObject.hpp"
#include "ivec2.hpp"
#include <map>
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
    bool isInsideCameraView(GameObject *object);
    void renderGameObjects(std::map<dis::ivec2, GameObject *> &gameObjects, float deltaTime);
    glm::vec3 getMouseWorldPosition(GLFWwindow *window);
    float getLeft() const { return (widthx); }
    float getRight() const { return (widthy); }
    float getBottom() const { return (heightx); }
    float getTop() const { return (heighty); }
private:
    Camera2D() : camPosition(0.0f, 0.0f, 0.0f), mtxProj(1.0f) {}
    float widthx;
    float widthy;
    float heightx;
    float heighty;
};

