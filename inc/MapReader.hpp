#pragma once

#include <vector>
#include "GameObject.hpp"

class MapReader
{
public:
    MapReader(int ac, char **av);
    ~MapReader();
    void readMap(const char *location);
    void createGameObjects();
    void drawMap(float deltaTime);
    void test(int x, int y);
private:
    std::vector<std::string> map;
    std::vector<GameObject *> gameObjects;
    int mapWidth;
    int mapHeight;
    void createMapObject(char c, int x, int y, std::string textureLocation = "./textures/missingTexture.jpeg");
    void createCollidableMapObject(char c, int x, int y, std::string textureLocation = "./textures/missingTexture.jpeg");
    void selectMapObject(char c, int x, int y);
};