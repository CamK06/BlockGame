#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "display.h"

namespace Graphics::Display
{

bool wireframe = false;

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
    glfwSetKeyCallback(*window, keyCallback);
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW
    glewInit();

    // Direct OpenGL stuff
    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_F3 && action == GLFW_RELEASE)
        toggleWireframe();
}

void toggleWireframe()
{
    wireframe = !wireframe;

    if(wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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