#include "game.h"
#include "graphics/util/display.h"
#include "util/log.h"

int Game::exec()
{
    // Display setup
    Log::write("Initializing BlockGame...");
    Graphics::Display::createWindow(&window);
    cube = new Graphics::CubeRenderer();
    camera = new Graphics::Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    glfwSetWindowUserPointer(window, camera);
    glfwSetCursorPosCallback(window, camera->mouse);

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
    // Calculate deltaTime
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    camera->update();
}

void Game::render()
{
    // Clear screen
    glClearColor(0.0f, 0.65f, 0.75f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw stuff
    cube->render(glm::vec3(0, 0, 0), camera);
    cube->render(glm::vec3(1, 0, 0), camera);
    cube->render(glm::vec3(-1, 0, 0), camera);
    cube->render(glm::vec3(0, 1, 0), camera);
    cube->render(glm::vec3(0, -1, 0), camera);
}

void Game::pollButtons()
{
    // Escape to exit
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    camera->input(window, deltaTime);
}