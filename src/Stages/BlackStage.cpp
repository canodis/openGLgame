// only black screen
#include "BlackStage.hpp"
#include "Scene.hpp"

BlackStage::BlackStage()
{
}

void BlackStage::initStage()
{
}

void BlackStage::runStage()
{
    if (glfwGetKey(Scene::getInstance().window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(Scene::getInstance().window))
    {
        Navigator::getInstance().exitGame();
    }
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(Scene::getInstance().window);
    glfwPollEvents();
}

void BlackStage::endStage() {}

BlackStage::~BlackStage() {}