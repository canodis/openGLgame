#include "MapController.hpp"
#include "MapObjectTypes.hpp"
#include "Scene.hpp"
#include <iostream>
#include <fstream>
#include <BoxCollision2dController.hpp>
#include "BoxCollision2d.hpp"

MapController::MapController(int ac, char **av) {
    readMap("./map.txt");
}

MapController::~MapController() { }

void    MapController::readMap(const char *location)
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

void    MapController::createGameObjects()
{
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; map[y][x]; x++)
        {
            selectMapObject(map[y][x], x, y);
        }
    }
}

void    MapController::selectMapObject(char c, int x, int y)
{
    switch (c)
    {
        case water:
            createCollidableMapObject(c, x, y, "./textures/grassSpriteSheet/water.png");
            break;
        case grassLeftUp:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/grassLeftUp.png");
            break;
        case grassUp:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/grassUp.png");
            break;
        case grassRightUp:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/grassRightUp.png");
            break;
        case grassLeft:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/grassLeft.png");
            break;
        case grassMiddle:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/grassMiddle.png");
            break;
        case grassRight:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/grassRight.png");
            break;
        case grassLeftDown:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/grassLeftDown.png");
            break;
        case grassDown:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/grassDown.png");
            break;
        case grassRightDown:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/grassRightDown.png");
            break;
        case rockLeftUp:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/rockLeftUp.png");
            break;
        case rockUp:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/rockUp.png");
            break;
        case rockRightUp:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/rockRightUp.png");
            break;
        case rockLeft:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/rockLeft.png");
            break;
        case rockMiddle:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/rockMiddle.png");
            break;
        case rockRight:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/rockRight.png");
            break;
        case rockLeftDown:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/rockLeftDown.png");
            break;
        case rockDown:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/rockDown.png");
            break;
        case rockRightDown:
            createMapObject(c, x, y, "./textures/grassSpriteSheet/rockRightDown.png");
            break;
    }
}

void    MapController::createCollidableMapObject(char c, int x, int y, std::string textureLocation)
{
    GameObject *gameObject = Scene::getInstance().gameObjectManager->Create2dObject("mapObject");
    gameObject->SetTexture(Scene::getInstance().textureManager->loadTexture(textureLocation));
    gameObject->SetShaderProgram(Scene::getInstance().shaderProgram);
    gameObject->setPosition(glm::vec3(-((float)x), -((float)y), 0.0f));
    gameObject->AddComponent<BoxCollision2d>();
    gameObject->setStatic();
    Scene::getInstance().boxCollision2dController->objects.insert({dis::ivec2(-x, -y), gameObject});
    mapObjects.insert({dis::ivec2(-x, -y), gameObject});
}

void    MapController::createMapObject(char c, int x, int y, std::string textureLocation)
{
    GameObject *gameObject = Scene::getInstance().gameObjectManager->Create2dObject("mapObject");
    gameObject->SetTexture(Scene::getInstance().textureManager->loadTexture(textureLocation));
    gameObject->SetShaderProgram(Scene::getInstance().shaderProgram);
    gameObject->setStatic();
    gameObject->setPosition(glm::vec3(-((float)x), -((float)y), 0.0f));
    mapObjects.insert({dis::ivec2(-x, -y), gameObject});
}

void    MapController::drawMap(float deltaTime)
{
    Camera2D::getInstance().renderGameObjects(mapObjects, deltaTime);
}
