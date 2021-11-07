#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../shader.h"
#include "../texture.h"

namespace Graphics
{

class QuadRenderer
{
public:
    QuadRenderer();
    void render();

private:
    Shader* shader;
    Texture* texture;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

}