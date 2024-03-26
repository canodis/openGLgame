#pragma once


#include <iostream>
#include <map>

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();
    void            init();
    unsigned int    loadTexture(const std::string filename);
    void            activateTexture(unsigned int level, unsigned int id);
    void            loadFromFolder(const std::string file);
    unsigned int    missingTexture;
private:
    std::map<std::string, unsigned int> m_textureMap;
};
