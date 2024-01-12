#include "TextureManager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad.h>

TextureManager::TextureManager() {
    missingTexture = loadTexture("textures/missingTexture.jpeg");
}

unsigned int TextureManager::loadTexture(const std::string filename)
{
    unsigned int id;

    if (m_textureMap.count(filename) != 0)
    {
        return m_textureMap[filename];
    }

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cerr << "Texture can not load: " << filename << std::endl;
        return -1;
    }

    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);

    GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);

    m_textureMap[filename] = id;

    return id;
}

void TextureManager::activateTexture(unsigned int level, unsigned int id)
{
    glActiveTexture(level);
    glBindTexture(GL_TEXTURE_2D, id);
}
