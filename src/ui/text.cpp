#include "text.h"

// This file is mostly directly taken from learnopengl because I'm lazy and fonts suck

#include "../graphics/shader.h"
#include "../util/log.h"

#include <map>

namespace Ui
{

FT_Library ft;
FT_Face face;
Graphics::Shader* shader;
glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(1280), 0.0f, static_cast<float>(720));
std::map<GLchar, TextChar> characters;

unsigned int VAO;
unsigned int VBO;

void InitText()
{
    // Shader setup
    shader = new Graphics::Shader("text.vs", "text.fs");
    shader->use();
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // FreeType setup
    if(FT_Init_FreeType(&ft)) {
        Log::write("Failed to initialize FreeType!");
        return;
    }

    // Load the font
    if(FT_New_Face(ft, "res/fonts/default.ttf", 0, &face)) {
        Log::write("Failed to load font!");
        return;
    }
    else {
        FT_Set_Pixel_Sizes(face, 0, 48);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Load first 128 characters
        for(unsigned char c = 0; c < 128; c++) {
            if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                Log::write("Failed to load font glyph");
                continue;
            }

            // Create a texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, 
                         GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            TextChar character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            characters.insert(std::pair<char, TextChar>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // Stop FreeType
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // Create VAO/VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    // Unbind VAO/VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void UpdateDisplay()
{
    int width, height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
    projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
}

void DisplayText(std::string text, float x, float y, float scale, glm::vec3 colour, bool centered)
{
    // Setup the render state
    shader->use();
    glUniform3f(glGetUniformLocation(shader->ID, "textColor"), colour.x, colour.y, colour.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // Calculate width and height of string if centered
    // TODO: Replace this with a better method. This is just a quick and easy hack
    float tW = 0.0f;
    float tH = 0.0f;
    if(centered) {
        std::string::const_iterator h;
        for(h = text.begin(); h != text.end(); h++) {
            TextChar ch = characters[*h];

            tW += (ch.size.x * scale);
            tH = (ch.size.y * scale);
        }
        y -= tH/2;
        x -= tW/2;
    }

    // Draw each character
    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++) {
        TextChar ch = characters[*c];

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;
        float xPos = x + ch.bearing.x * scale;
        float yPos = y - (ch.size.y - ch.bearing.y) * scale;

        float vertices[6][4] = {
            { xPos,     yPos + h,   0.0f, 0.0f },            
            { xPos,     yPos,       0.0f, 1.0f },
            { xPos + w, yPos,       1.0f, 1.0f },

            { xPos,     yPos + h,   0.0f, 0.0f },
            { xPos + w, yPos,       1.0f, 1.0f },
            { xPos + w, yPos + h,   1.0f, 0.0f } 
        };

        glBindTexture(GL_TEXTURE_2D, ch.texID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.advance >> 6) * scale;
    }

    // Unbind VAO/VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

}