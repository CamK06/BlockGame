#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "display.h"

namespace Graphics::Display
{

void createWindow(GLFWwindow** window)
{
    // Initialize GLFW
    if(!glfwInit()) // TODO: Add fail message
        return;
    glfwWindowHint(GL_MINOR_VERSION, 3);
    glfwWindowHint(GL_MAJOR_VERSION, 3);
    *window = glfwCreateWindow(WIDTH, HEIGHT, "BlockGame", NULL, NULL);
    glfwMakeContextCurrent(*window);
    glfwSetWindowSizeCallback(*window, windowSizeUpdated);
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW
    glewInit();

    // Direct OpenGL stuff
    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void terminate()
{
    glfwTerminate();
}

void windowSizeUpdated(GLFWwindow* window, int x, int y)
{
    glViewport(0, 0, x, y);
}

}