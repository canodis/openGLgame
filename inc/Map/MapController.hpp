#pragma once

#include <vector>
#include "GameObject.hpp"
#include "ivec2.hpp"

class MapController
{
public:
    MapController(int ac, char **av);
    ~MapController();
    void readMap(const char *location);
    void createGameObjects();
    void drawMap(float deltaTime);
    void test(int x, int y);
private:
    std::vector<std::string> map;
    std::map<dis::ivec2, GameObject *> mapObjects;
    int mapWidth;
    int mapHeight;
    void createMapObject(char c, int x, int y, std::string textureLocation = "./textures/missingTexture.jpeg");
    void createCollidableMapObject(char c, int x, int y, std::string textureLocation = "./textures/missingTexture.jpeg");
    void selectMapObject(char c, int x, int y);
};