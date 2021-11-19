#include "level.h"
#include "block.h"
#include <iostream>
#include <algorithm>

namespace World
{

Level::Level(int width, int height, int depth, Graphics::Camera* camera)
{
    this->width = width;
    this->height = height;
    this->depth = depth;
    this->camera = camera;

    // Create blocks
    blocks = new int[width*height*depth];
    for(int i = 0; i < width*height*depth; i++)
        blocks[i] = BLOCK_AIR;

    // Create chunks
    chunks = new Chunk[(width/16)*(height/16)];
    for(int i = 0; i < width/16; i++)
        for(int j = 0; j < height/16; j++) {
            Chunk newChunk(i, j, this);
            chunks[j * (width/16) + i] = newChunk;
        }

    // Create worldgen
    worldGen = new Generator(this);

    // Start the chunk generation/swapping thread
    chunkWorkerThread = std::thread(&Level::chunkWorker, this);
    isWorkerRunning = true;
}

void Level::chunkWorker()
{
    while(isWorkerRunning) {
        
        int cx = (int)camera->pos.x/16;
        int cy = (int)camera->pos.z/16;

        // Check and build all chunks in a 3x3 grid around the player
        // TODO: Make the distance adjustable & clean up code
        for(int i = -3; i < 3; i++) {
            for(int j = -3; j < 3; j++) { 
                Chunk* chunk = getChunk(cx+i, cy+j);
                if(chunk != nullptr && !chunk->hasMesh) {
                    chunk->isDirty = true;
                    chunk->hasMesh = true;
                }
            }
        }
    }
}

void Level::render()
{
    for(int i = 0; i < width/16; i++) {
        for(int j = 0; j < height/16; j++) {
            Chunk* chunk = getChunk(i, j);
            if(chunk != nullptr)
                chunk->render(camera);
        }
    }
}

void Level::cleanup()
{
    isWorkerRunning = false;
    if(chunkWorkerThread.joinable()) { chunkWorkerThread.join(); }
    delete chunks;
}

void Level::updateAspect() {
    for(int i = 0; i < width/16; i++) {
        for(int j = 0; j < height/16; j++) {
            chunks[j * (width/16) + i].updateAspect();
        }
    }
}

void Level::setBlock(int x, int y, int z, int blockType)
{
    // Return if the block is outside of the level
    if(x < 0 || y < 0 || z < 0 || x >= width || y >= depth || z >= height)
        return;

    blocks[(y * height + z) * width + x] = blockType;
}

bool Level::isBlock(int x, int y, int z)
{
    // Check if the block is outside of the level
    if(x < 0 || y < 0 || z < 0 || x >= width || y >= depth || z >= height)
        return false;

    return blocks[(y * height + z) * width + x] != BLOCK_AIR;
}

int Level::getBlock(int x, int y, int z)
{
    return blocks[(y * height + z) * width + x];
}

bool Level::isSolidBlock(int x, int y, int z)
{
    return isBlock(x, y, z);
}

Chunk* Level::getChunk(int x, int z)
{
    int index = z * (width/16) + x;
    if(index < 0 || index > (width/16)*(height/16))
        return nullptr;

    return &chunks[index];
}

void Level::regenChunks()
{
    for(int i = 0; i < width/16; i++) {
        for(int j = 0; j < height/16; j++) {
            chunks[j * (width/16) + i].isDirty = true;
        }
    }
}

}