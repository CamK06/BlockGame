#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/renderers/cuberenderer.h"
#include "graphics/camera.h"

class Game
{
public:
    int exec();

private:
    void update();
    void render();
    void pollButtons();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    GLFWwindow* window;
    Graphics::CubeRenderer* cube;
    Graphics::Camera* camera;
};