#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

namespace Ui
{

struct TextChar {
    unsigned int texID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

void InitText();
void UpdateDisplay();
void DisplayText(std::string text, float x, float y, float scale, glm::vec3 colour, bool centered = true);

}