#pragma once

#include "block.h"
#include "chunk.h"
#include "generator.h"

#include <thread>

namespace World
{

class Chunk;
class Generator;

class Level
{
public:
    Level(int width, int height, int depth, Graphics::Camera* camera);
    
    void render();
    void updateAspect();
    void chunkWorker();

    bool isSolidBlock(int x, int y, int z);
    bool isBlock(int x, int y, int z);
    void setBlock(int x, int y, int z, int blockType);
    int getBlock(int x, int y, int z);
    Chunk* getChunk(int x, int z);
    void regenChunks();

    void cleanup();

    int width, height, depth;
    int renderDistance = 6;
    Generator* worldGen;

private:
    Chunk* chunks;
    Graphics::Camera* camera;
    int* blocks;

    std::thread chunkWorkerThread;
    bool isWorkerRunning = true;
};

}