#include "MapReader.hpp"
#include "MapObjectTypes.hpp"
#include "Scene.hpp"
#include <iostream>
#include <fstream>
#include <ComponentCreator.hpp>
#include <BoxCollision2dController.hpp>

MapReader::MapReader(int ac, char **av) {
    // if (ac != 2)
    // {
    //     std::cout << "Usage: ./my_rpg map_location" << std::endl;
    //     exit(1);
    // }
    readMap("./map.txt");
}

MapReader::~MapReader() {
}

void    MapReader::readMap(const char *location)
{
    std::ifstream file(location);

    if (!file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        exit(1);
    }
    std::string line;
    std::string allLines;
    while (std::getline(file, line))
    {
        map.push_back(line);
    }
    mapWidth = map[0].size();
    mapHeight = map.size();
}

void    MapReader::createGameObjects()
{
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; map[y][x]; x++)
        {
            selectMapObject(map[y][x], x, y);
        }
    }
}

void    MapReader::selectMapObject(char c, int x, int y)
{
    switch (c)
    {
        case background:
            createMapObject(c, x, y, "./textures/background.jpeg");
            break;
        case grass:
            createCollidableMapObject(c, x, y, "./textures/grass.jpeg");
            break;
        case stone:
            createMapObject(c, x, y, "./textures/stone.png");
            break;
        case player:
            createMapObject(c, x, y, "./textures/player.png");
            break;
        default:
            std::cout << "Error: Unknown map object : " << c <<  std::endl;
            break;
    }
}

void    MapReader::createCollidableMapObject(char c, int x, int y, std::string textureLocation)
{
    GameObject *gameObject = Scene::getInstance().gameObjectManager->Create2dObject("mapObject");
    gameObject->SetTexture(Scene::getInstance().textureManager->loadTexture(textureLocation));
    gameObject->SetShaderProgram(Scene::getInstance().shaderProgram);
    gameObject->transform.position = glm::vec3(-((float)x), -((float)y), 0.0f);
    gameObject->isStatic = true;
    Scene::getInstance().boxCollision2dController->objects.insert({dis::ivec2(-x, -y), gameObject});

    // gameObject->Update(0.0f);
    gameObjects.push_back(gameObject);
}

void    MapReader::createMapObject(char c, int x, int y, std::string textureLocation)
{
    GameObject *gameObject = Scene::getInstance().gameObjectManager->Create2dObject("mapObject");
    gameObject->SetTexture(Scene::getInstance().textureManager->loadTexture(textureLocation));
    gameObject->SetShaderProgram(Scene::getInstance().shaderProgram);
    gameObject->transform.position = glm::vec3(-((float)x), -((float)y), 0.0f);
    gameObject->isStatic = true;
    // gameObject->Update(0.0f);
    gameObjects.push_back(gameObject);
}

void    MapReader::drawMap(float deltaTime)
{
    for (auto &object : gameObjects)
    {
       object->update(deltaTime);
    }
}