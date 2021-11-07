#pragma once

#include <GLFW/glfw3.h>

#define WIDTH 1280
#define HEIGHT 720

namespace Graphics::Display
{
    void createWindow(GLFWwindow** window);
    void windowSizeUpdated(GLFWwindow* window, int x, int y);
    void terminate();
}