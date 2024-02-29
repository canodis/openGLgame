#include "Game.hpp"
#include "NpcController.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

int main(int ac, char **av)
{
    Player *player = new Player();
    Client::getInstance();
    MapController mapController(ac, av);
    Scene *scene = &Scene::getInstance();
    scene->player = player;
    mapController.loadMap();

    Camera2D& camera = Camera2D::getInstance();
    scene->timer->start();
    GameObject *effect = scene->gameObjectManager->Create2dObject("a");
    effect->setPosition(glm::vec3(0, 0, 0));
    Animator *anim = effect->AddComponent<Animator>();
    anim->loadTexturesFromDirectory(AnimationType::idle, "./animations/TestEffect/", "effect", "png", 0.03f);
    anim->setCurrentAnimation(AnimationType::idle);
    NpcController *npcController = &NpcController::getInstance();
    effect->SetShaderProgram(scene->shaderProgram);
    scene->shaderProgram->setVec2("lightPosition", glm::vec2(0, 0));
    scene->shaderProgram->setFloat("lightInstensity", 0.08f);
    while (glfwGetKey(scene->window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(scene->window))
    {
        scene->shaderProgram->use();
        glClear(GL_COLOR_BUFFER_BIT);
        float delta = scene->timer->elapsedSeconds();
        player->processInput(scene->window, delta);
        
        scene->shaderProgram->setVec2("lightPosition", glm::vec2(player->GetPosition().x, player->GetPosition().y));
        mapController.drawMap(delta);
        npcController->update(delta);
        Client::getInstance().renderPlayers(delta);
        scene->DrawGameObjects(delta);
        player->Update(delta);
        camera.followPoint(scene->window, player->GetPosition());
        scene->shaderProgram->setMat4("viewMatrix", &camera.mtxProj);
        scene->textRenderer->ShowPlayerInfo();
        effect->update(delta);
        camera.update(scene->window, delta);
        player->ResetVelocity();
        glfwSwapBuffers(scene->window);
        glfwPollEvents();
    }
}
