#pragma once

#include "../graphics/renderers/chunkrenderer.h"
#include "../graphics/camera.h"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16
#define CHUNK_DEPTH 256

namespace Graphics {
    class ChunkRenderer;
}

namespace World
{

class Level;

class Chunk
{
public:
    Chunk() = default;
    Chunk(int x, int z, Level* level);
    void render(Graphics::Camera* camera);
    void rebuild();
    void updateAspect();
    void destroy();

    int x;
    int z;
    bool isDirty;
    bool hasMesh = false;

private:
    Graphics::ChunkRenderer* renderer;
    Level* level;
};

}