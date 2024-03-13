#include "MapController.hpp"
#include "Scene.hpp"
#include <iostream>
#include <fstream>
#include <BoxCollision2dController.hpp>
#include "BoxCollision2d.hpp"
#include <sstream>

MapController::MapController(int ac, char **av)
{
}

MapController::MapController() {}

MapController::~MapController() {}

void MapController::drawMap(float deltaTime)
{
    Camera2D::getInstance().renderMapObjects(map, deltaTime);
}

void MapController::loadMap()
{
    std::fstream file;
    file.open("map.txt", std::ios::in);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            float x, y;
            std::string texturePath;
            int layer;
            bool isCollidable;
            if (!(iss >> x >> y >> texturePath >> layer >> isCollidable))
            {
                continue;
            }
            addToMap(dis::ivec2(x, y), Scene::getInstance().textureManager->loadTexture(texturePath), layer, texturePath, isCollidable);
        }
    }
    file.close();
}

void MapController::addToMap(dis::ivec2 pos, unsigned int textureId, int layer, std::string texturePath, bool isCollidable)
{
    MapObject *mapObject = new MapObject(glm::ivec3(pos.x, pos.y, 0), textureId, layer, isCollidable);
    if (isCollidable)
    {
        mapObject->m_gameObject->AddComponent<BoxCollision2d>();
        Scene::getInstance().boxCollision2dController->objects.insert({pos, mapObject->m_gameObject});
    }
    if (map[layer].find(pos) != map[layer].end())
    {
        delete map[layer][pos];
        map[layer].erase(pos);
    }
    map[layer][pos] = mapObject;
    map[layer][pos]->texturePath = texturePath;
    mapObject->m_gameObject->setStatic();
}

void MapController::removeFromMap(dis::ivec2 pos, int layer)
{
    dis::ivec2 obj(pos.x, pos.y);
    if (map[layer].find(obj) != map[layer].end())
    {
        delete map[layer][obj];
        map[layer].erase(obj);
    }
}

MapObject *MapController::getObjectAt(dis::ivec2 pos)
{
    std::map<int, std::map<dis::ivec2, MapObject *>>::reverse_iterator it;
    for (it = map.rbegin(); it != map.rend(); it++)
    {
        if (it->second.find(pos) != it->second.end())
        {
            return it->second[pos];
        }
    }
    return NULL;
}
