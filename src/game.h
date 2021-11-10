#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/renderers/cuberenderer.h"

class Game
{
public:
    int exec();

private:
    void update();
    void render();
    void pollButtons();

    GLFWwindow* window;
    Graphics::CubeRenderer* cube;
};