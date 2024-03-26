#include "MainStage.hpp"
#include "BlackStage.hpp"

MainStage::MainStage()
{
    scene = &Scene::getInstance();
}

void MainStage::initStage()
{
    player = new Player();
    player->init(3.0f);
    Scene::getInstance().textureManager->init();
    Client::getInstance();
    scene->player = player;
    mapController.loadMap();
    camera = &Camera2D::getInstance();
    scene->timer->start();
    npcController = &NpcController::getInstance();
    scene->shaderProgram->setVec2("lightPosition", glm::vec2(0, 0));
    scene->shaderProgram->setFloat("lightInstensity", 0.03f);
}

void MainStage::runStage()
{
    if (glfwGetKey(scene->window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(scene->window))
    {
        Navigator::getInstance().exitGame();
        return;
    }
    scene->shaderProgram->use();
    glClear(GL_COLOR_BUFFER_BIT);
    float delta = scene->timer->elapsedSeconds();
    player->processInput(*scene->window, delta);
    scene->shaderProgram->setVec2("lightPosition", glm::vec2(player->GetPosition().x, player->GetPosition().y));
    mapController.drawMap(delta);
    npcController->update(delta);
    Client::getInstance().renderPlayers(delta);
    scene->DrawGameObjects(delta);
    player->update(delta);
    camera->followPoint(player->GetPosition());
    scene->shaderProgram->setMat4("viewMatrix", &camera->mtxProj);
    scene->textRenderer->ShowPlayerInfo();
    camera->update(*scene->window, delta);
    player->ResetVelocity();
    glfwSwapBuffers(scene->window);
    glfwPollEvents();
}

void MainStage::endStage()
{
    delete player;
}

MainStage::~MainStage() {}

void MainStage::terminateThreads()
{
    Client::getInstance().terminate();
}