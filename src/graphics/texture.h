#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Graphics
{

class Texture
{
public:
    Texture(const char* fileName);
    void use();

    unsigned int ID;
    int width;
    int height;
    int channels;

private:
};

}