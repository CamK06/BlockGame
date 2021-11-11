#include "game.h"
#include "graphics/util/display.h"
#include "util/log.h"

#include "util/perlin.hpp"

#include <iomanip>
#include <iostream>

int Game::exec()
{
    // Display setup
    Log::write("Initializing BlockGame...");
    Graphics::Display::createWindow(&window);
    level = new World::Level(32, 32, 256);
    camera = new Graphics::Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    for(int i = 0; i < 32; i++) {
        for(int j = 0; j < 32; j++) {
            for(int k = 0; k < 32/*+(perlin::noise(i/100.0f, j/100.0f)*10)*/; k++) {
                level->setBlock(i, k, j, BLOCK_GRASS);
            }
        }
    }
    level->updateMesh();
    
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
    glClearColor(0.0f, 0.5f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw stuff
    level->render(glm::vec3(0, -35, 0), camera);
}

void Game::pollButtons()
{
    // Escape to exit
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    camera->input(window, deltaTime);
}