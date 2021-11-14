#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/renderers/blockrenderer.h"
#include "graphics/camera.h"

#include "world/block.h"
#include "world/level.h"

class Game
{
public:
    Game() = default;
    int exec();
    void updateAspect();
    void keyPressed(int key);
    void keyReleased(int key);

private:
    void update();
    void render();
    void pollButtons();

    float deltaTime = 0.0f;
    float lastTime = 0.0f;
    float fpsLastTime = 0.0f;
    int fps = 0;
    int frameCount = 0;

    bool fullscreen = false;

    GLFWwindow* window;
    int windowWidth = 1280;
    int windowHeight = 720;

    Graphics::CubeRenderer* cube;
    Graphics::Camera* camera;
    World::Level* level;

};