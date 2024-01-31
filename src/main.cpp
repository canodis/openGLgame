#include "Game.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H  

int main(int ac, char **av)
{
    Client::getInstance();
    MapController mapController(ac, av);
    Camera2D::getInstance().SetProjection(-5.0f, 5.0f, -3.0f, 7.0f);
    Player *player = new Player();
    Scene::getInstance().player = player;
    mapController.createGameObjects();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glfwSwapInterval(0);
    Scene::getInstance().timer->start();
    Scene::getInstance().timer->setMaxFPS(4564);
    while (glfwGetKey(Scene::getInstance().window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(Scene::getInstance().window))
    {
        Scene::getInstance().shaderProgram->use();
        glClear(GL_COLOR_BUFFER_BIT);
        float delta = Scene::getInstance().timer->elapsedSeconds();
        glfwSetWindowTitle(Scene::getInstance().window, std::to_string(1.0f / delta).c_str());
        player->processInput(Scene::getInstance().window, delta);
        mapController.drawMap(delta);
        Client::getInstance().renderPlayers(delta);
        Scene::getInstance().DrawGameObjects(delta);
        player->Update(delta);
        Camera2D::getInstance().followPoint(Scene::getInstance().window, player->GetPosition());
        Scene::getInstance().shaderProgram->setMat4("viewMatrix", &Camera2D::getInstance().mtxProj);
        Scene::getInstance().textRenderer->ShowPlayerInfo();
        player->ResetVelocity();
        glfwSwapBuffers(Scene::getInstance().window);
        glfwPollEvents();
    }
}
