#include "Game.hpp"
#include "NpcController.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

int main(int ac, char **av)
{
    Player *player = new Player();
    Animator *anim = new Animator();
    Client::getInstance();
    MapController mapController(ac, av);
    Scene *scene = &Scene::getInstance();
    scene->player = player;
    mapController.loadMap();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    Camera2D *camera = &Camera2D::getInstance();
    glfwSwapInterval(0);
    scene->timer->start();
    NpcController *npcController = &NpcController::getInstance();
    while (glfwGetKey(scene->window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(scene->window))
    {
        scene->shaderProgram->use();
        glClear(GL_COLOR_BUFFER_BIT);
        float delta = scene->timer->elapsedSeconds();
        player->processInput(scene->window, delta);
        mapController.drawMap(delta);
        npcController->update(delta);
        scene->DrawGameObjects(delta);
        Client::getInstance().renderPlayers(delta);
        player->Update(delta);
        camera->getInstance().followPoint(scene->window, player->GetPosition());
        scene->shaderProgram->setMat4("viewMatrix", &camera->getInstance().mtxProj);
        scene->textRenderer->ShowPlayerInfo();
        camera->update(scene->window, delta);
        player->ResetVelocity();
        glfwSwapBuffers(scene->window);
        glfwPollEvents();
    }
}
