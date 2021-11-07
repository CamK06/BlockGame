#pragma once

#include <GLFW/glfw3.h>

class Game
{
public:
    int exec();

private:
    void update();
    void render();
    void pollButtons();

    GLFWwindow* window;
};