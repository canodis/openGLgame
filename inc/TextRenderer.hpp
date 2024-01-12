#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <iostream>
#include "../glm/glm.hpp"
#include <map>
#include "ShaderProgram.hpp"

struct Character {
    unsigned int TextureID;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    long Advance;
};

class TextRenderer
{
public:
    TextRenderer();
    void init();
    void renderText(std::string text, float x, float y, float scale, glm::vec3 color);
    void ShowPlayerInfo();
    void setMat4(const std::string &name, const glm::mat4 *value);
private:
    ShaderProgram *shaderProgram;
    FT_Library ft;
    FT_Face face;
    std::map<char, Character> Characters;
    unsigned int VAO;
    unsigned int VBO;
    float textXpos;
    float textYpos;
    float textWidth;
    float textHeight;
};
