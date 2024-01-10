#include "Game.hpp"

int main(int ac, char **av)
{
    Camera2D::getInstance().SetProjection(-10.0f, 10.0f, -10.0f, 10.0f);

    Scene::getInstance().shaderProgram->addUniform("mtxTransform");
    Scene::getInstance().shaderProgram->addUniform("textureSampler");
    Player *player = new Player();
    glm::mat4 mtxTransform;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Scene::getInstance().player = player;

    while (glfwGetKey(Scene::getInstance().window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(Scene::getInstance().window))
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        Camera2D::getInstance().Update(Scene::getInstance().window);
        player->processInput(Scene::getInstance().window, Scene::getInstance().timer->elapsedSeconds());
        Scene::getInstance().shaderProgram->setMat4("mtxTransform", &Camera2D::getInstance().mtxProj);
        for (auto &object : Scene::getInstance().gameObjects)
        {
            object->UpdateTransform();
            object->Draw();
        }

        glfwSwapBuffers(Scene::getInstance().window);
        glfwPollEvents();
    }
}
