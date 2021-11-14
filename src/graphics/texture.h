#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <string>

namespace Graphics
{

struct UV
{
    int textureID;
    float u, v;
};

class Texture
{
public:
    Texture(std::string fileName);
    void use();

    unsigned int ID;
    int width;
    int height;
    int channels;

private:
    static std::map<std::string, unsigned int> textures;
};

}