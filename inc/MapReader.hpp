#pragma once

#include <vector>
#include "GameObject.hpp"

class MapReader
{
public:
    MapReader(int ac, char **av);
    void readMap(char *location);
    void createGameObjects();
    void drawMap(float deltaTime);
    ~MapReader();
private:
    std::vector<std::string> map;
    std::vector<GameObject *> gameObjects;
    int mapWidth;
    int mapHeight;
    void createMapObject(char c, int x, int y, std::string textureLocation = "./textures/background.png");
    void selectMapObject(char c, int x, int y);
};