#pragma once

#include <vector>
#include "GameObject.hpp"
#include "MapObject.hpp"
#include "ivec2.hpp"
#include <map>

class MapController
{
public:
    MapController(int ac, char **av);
    MapController();
    ~MapController();
    void drawMap(float deltaTime);
    void loadMap();
    void removeFromMap(dis::ivec2 pos, int layer);
private:
    void addToMap(dis::ivec2 pos, unsigned int textureId, int layer, std::string texturePath, bool isCollidable);
    MapObject *getObjectAt(dis::ivec2 pos);
    std::map<dis::ivec2, GameObject *> mapObjects;
    int mapWidth;
    int mapHeight;
    void createCollidableMapObject(char c, int x, int y, std::string textureLocation = "./textures/missingTexture.jpeg");
    std::map<int, std::map<dis::ivec2, MapObject *>> map;
};