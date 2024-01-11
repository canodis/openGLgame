#include "Game.hpp"

int main(int ac, char **av)
{
    MapReader mapReader(ac, av);
    Camera2D::getInstance().SetProjection(-5.0f, 5.0f, -5.0f, 5.0f);

    Scene::getInstance().shaderProgram->addUniform("mtxTransform");
    Scene::getInstance().shaderProgram->addUniform("textureSampler");
    Scene::getInstance().shaderProgram->addUniform("viewMatrix");
    Player *player = new Player();
    player->obj->transform.position = glm::vec3(-25.0f, -3.0f, 0.0f);
    glm::mat4 mtxTransform;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    player->obj->AddComponent(ComponentCreator::Create<GravityComponent>());
    Scene::getInstance().player = player;
    mapReader.createGameObjects();

    while (glfwGetKey(Scene::getInstance().window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(Scene::getInstance().window))
    {
        float delta = Scene::getInstance().timer->elapsedSeconds();
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        Camera2D::getInstance().Update(Scene::getInstance().window, {player->obj->transform.position.x, player->obj->transform.position.y});
        player->processInput(Scene::getInstance().window, delta);
         Scene::getInstance().shaderProgram->setMat4("viewMatrix", &Camera2D::getInstance().mtxProj);
        mapReader.drawMap(delta);
        for (auto &object : Scene::getInstance().gameObjects)
            object->Update(delta);
        std::cout << player->obj->transform.position.x << " " << player->obj->transform.position.y << std::endl;
        glfwSwapBuffers(Scene::getInstance().window);
        glfwPollEvents();
    }
}
