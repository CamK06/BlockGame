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
    camera = new Graphics::Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // Game setup
    level = new World::Level(128, 128, 256);

    // World generation
    siv::PerlinNoise perlin(time(0));
    for(int i = 0; i < 512; i++) {
        for(int j = 0; j < 512; j++) {
            int genHeight = 32+(perlin.noise2D(i/100.0f, j/100.0f)*10);
            for(int k = 0; k < genHeight; k++) {

                if(k >= genHeight-3) // Generate grass if we're in the top 3 blocks
                    level->setBlock(i, k, j, BLOCK_GRASS);
                else // Otherwise generate stone
                    level->setBlock(i, k, j, BLOCK_STONE);
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