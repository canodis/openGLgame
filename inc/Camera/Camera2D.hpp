#pragma once

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "GameObject.hpp"
#include "ivec2.hpp"
#include "MapObject.hpp"
#include <map>
#define BEGINX 0.0f
#define BEGINY 0.0f

class GLFWwindow;

class Camera2D
{
public:
    static Camera2D &getInstance()
    {
        static Camera2D instance;
        return instance;
    }
    Camera2D(Camera2D const &) = delete;
    void operator=(Camera2D const &) = delete;
    void update(GLFWwindow *window, float deltaTime);
    void followPoint(GLFWwindow *window, glm::vec2 point);
    void setProjection(float left, float right, float bottom, float top);
    bool isInsideCameraView(GameObject *object);
    void renderGameObjects(std::map<dis::ivec2, GameObject *> &gameObjects, float deltaTime);
    void renderMapObjects(std::map<int, std::map<dis::ivec2, MapObject *>> &objects, float deltaTime);
    glm::vec3 getMouseWorldPosition(GLFWwindow *window);
    glm::mat4 GetViewMatrix() const;
    float getLeft() const { return (widthx); }
    float getRight() const { return (widthy); }
    float getBottom() const { return (heightx); }
    float getTop() const { return (heighty); }
    glm::mat4 mtxProj;

private:
    Camera2D() : camPosition(0.0f, 0.0f, 0.0f), mtxProj(1.0f) { setProjection(-7.0f, 7.0f, -5.0f, 9.0f); _counter = 0; }
    float widthx;
    float widthy;
    float heightx;
    float heighty;
    glm::vec3 camPosition;
    float _counter;
};
