#include "TextRenderer.hpp"
#include <glad.h>
#include <Scene.hpp>

TextRenderer::TextRenderer()
{
    init();
    if (FT_Init_FreeType(&ft))
    {
        std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }
    if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return;
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer);
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x};
        Characters.insert(std::pair<char, Character>(c, character));
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::init()
{
    shaderProgram = new ShaderProgram("shaders/VertexTextRendererShader.glsl", "shaders/FragmentTextRenderer.glsl");
    shaderProgram->addUniform("projection");
}

void TextRenderer::renderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    shaderProgram->use();
    glUniform3f(glGetUniformLocation(shaderProgram->getProgramId(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        textXpos = x + ch.Bearing.x * scale;
        textYpos = y - (ch.Size.y - ch.Bearing.y) * scale;

        textWidth = ch.Size.x * scale;
        textHeight = ch.Size.y * scale;
        float vertices[6][4] = {
            { textXpos,     textYpos + textHeight,   0.0f, 0.0f },            
            { textXpos,     textYpos,       0.0f, 1.0f },
            { textXpos + textWidth, textYpos,       1.0f, 1.0f },

            { textXpos,     textYpos + textHeight,   0.0f, 0.0f },
            { textXpos + textWidth, textYpos,       1.0f, 1.0f },
            { textXpos + textWidth, textYpos + textHeight,   1.0f, 0.0f }           
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.Advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void    TextRenderer::ShowPlayerInfo()
{
    TextRenderer *textRenderer = Scene::getInstance().textRenderer;
    textRenderer->shaderProgram->use();
    Player *player = Scene::getInstance().player;
    textRenderer->renderText("Player Position: " + std::to_string(player->GetPosition().x) + ", " + std::to_string(player->GetPosition().y), -4.9f, 4.5f, 0.004f, glm::vec3(1.0f, 1.0f, 0.0f));
    textRenderer->renderText("Player Velocity: " + std::to_string(player->GetVelocity().x) + ", " + std::to_string(player->GetVelocity().y), -4.9f, 4.2f, 0.004f, glm::vec3(1.0f, 1.0f, 0.0f));
    textRenderer->setMat4("projection", &Camera2D::getInstance().mtxProj);
}

void    TextRenderer::setMat4(const std::string &name, const glm::mat4 *value)
{
    shaderProgram->setMat4(name, value);
}