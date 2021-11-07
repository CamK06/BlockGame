#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../shader.h"

namespace Graphics
{

class QuadRenderer
{
public:
    QuadRenderer();
    void render();

private:
    float* vertexes;
    Shader* shader;
};

}