#include "game.h"
#include "graphics/util/display.h"
#include "util/log.h"

int Game::exec()
{
    // Display setup
    Log::write("Initializing BlockGame...");
    Graphics::Display::createWindow(&window);
    quad = new Graphics::QuadRenderer();

    // Game loop
    while(!glfwWindowShouldClose(window)) {
        pollButtons();
        update();
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Exit
    Graphics::Display::terminate();
    Log::write("Exiting...");
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
    quad->render();
}

void Game::pollButtons()
{
    // Escape to exit
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}