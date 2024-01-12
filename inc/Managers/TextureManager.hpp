#pragma once


#include <iostream>
#include <map>

class TextureManager
{
public:
    TextureManager();
    unsigned int    loadTexture(const std::string filename);
    void            activateTexture(unsigned int level, unsigned int id);
    unsigned int    missingTexture;
private:
    std::map<std::string, unsigned int> m_textureMap;
};
