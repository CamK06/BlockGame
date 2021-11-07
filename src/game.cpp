#include "game.h"
#include "display.h"

int Game::exec()
{
    // Display setup
    Display::createWindow(&window);

    // Game loop
    while(!glfwWindowShouldClose(window)) {
        pollButtons();
        update();
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void Game::update()
{

}

void Game::render()
{
    // Clear screen
    glClearColor(0.0f, 0.65f, 0.75f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw stuff
}

void Game::pollButtons()
{
    // Escape to exit
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}