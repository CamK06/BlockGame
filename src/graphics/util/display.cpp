#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "display.h"
#include "../../game.h"

namespace Graphics::Display
{

bool wireframe = false;
Game* game1;

void createWindow(GLFWwindow** window, Game* game)
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

    // Configure OpenGL
    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    game1 = game;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_F3 && action == GLFW_RELEASE)
        toggleWireframe();

    game1->keyPressed(key);
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
    game1->updateAspect();
}

}