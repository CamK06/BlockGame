#include "game.h"
#include "graphics/util/display.h"
#include "ui/text.h"

#include "util/log.h"
#include "util/perlin.hpp"

#include <iomanip>
#include <iostream>

int Game::exec()
{
    // Display setup
    Log::write("Initializing BlockGame...");
    Graphics::Display::createWindow(&window, this);
    Ui::InitText();
    windowWidth = WIDTH;
    windowHeight = HEIGHT;

    // First render, for a loading screen
    glClearColor(0.0f, 0.5f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Ui::DisplayText("Generating world...", windowWidth/2, windowHeight/2, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    glfwSwapBuffers(window);

    // Game setup
    camera = new Graphics::Camera(glm::vec3(0.0f, 75.0f, 0.0f));
    level = new World::Level(128, 128, 256, camera);
    World::Block::initBlocks();

    glfwSetWindowUserPointer(window, camera);
    glfwSetCursorPosCallback(window, camera->mouse);

    fpsLastTime = lastTime = glfwGetTime();

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
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // FPS Calculation
    frameCount++;
    if(currentTime - fpsLastTime >= 1.0) {
        fps = frameCount;
        frameCount = 0;
        fpsLastTime = currentTime;
    }

    camera->update();
}

void Game::render()
{
    // Clear screen
    glClearColor(0.0f, 0.5f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw stuff
    level->render();

    // FPS Display
    char fpsText[16];
    char coordsText[64];
    sprintf(fpsText, "FPS: %d", fps);
    Ui::DisplayText(fpsText, 10, windowHeight-40, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), false);

    sprintf(coordsText, "X: %.1f", camera->pos.x);
    Ui::DisplayText(coordsText, 10, windowHeight-80, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), false);
    sprintf(coordsText, "Y: %.1f", camera->pos.y);
    Ui::DisplayText(coordsText, 10, windowHeight-120, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), false);
    sprintf(coordsText, "Z: %.1f", camera->pos.z);
    Ui::DisplayText(coordsText, 10, windowHeight-160, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), false);
}

void Game::keyPressed(int key)
{
    // F11 fullscreen toggle
    if(key == GLFW_KEY_F11) {
        if(!fullscreen) {
            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
            fullscreen = true;
        }
        else {
            glfwSetWindowMonitor(window, nullptr, 0, 0, WIDTH, HEIGHT, 60);
            fullscreen = false;
        }
    }
    // Escape to exit
    if(key == GLFW_KEY_ESCAPE) {
        level->cleanup();
        glfwSetWindowShouldClose(window, true);
    }
}

void Game::keyReleased(int key)
{
    // F2 wireframe toggle
    if(key == GLFW_KEY_F2)
        Graphics::Display::toggleWireframe();
}

void Game::pollButtons()
{   
    camera->input(window, deltaTime);
}

// I really need a better way to do this... calling so many functions is dumb.
// TODO: Maybe just make a pointer directly to the needed function
void Game::updateAspect() {
    level->updateAspect();
    Ui::UpdateDisplay();

    glfwGetWindowSize(window, &windowWidth, &windowHeight);
}