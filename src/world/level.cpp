#include "level.h"
#include "block.h"

namespace World
{

Level::Level(int width, int height, int depth)
{
    this->width = width;
    this->height = height;
    this->depth = depth;
    blocks = new int[width*height*depth];
    for(int i = 0; i < width*height*depth; i++)
        blocks[i] = BLOCK_AIR;
    chunks = new Chunk[(width/16)*(height/16)];
    for(int i = 0; i < width/16; i++)
        for(int j = 0; j < height/16; j++) {
            Chunk newChunk(i, j, this);
            chunks[j * (width/16) + i] = newChunk;
        }
}

Chunk* Level::getChunk(int x, int z)
{
    return &chunks[z * (width/16) + x];
}

void Level::render(Graphics::Camera* camera)
{
    for(int i = 0; i < width/16; i++) {
        for(int j = 0; j < height/16; j++) {
            Chunk* chunk = getChunk(i, j);
            if(chunk != nullptr)
                chunk->render(camera);
        }
    }
    //chunks[0].render(camera);
    //chunks[1].render(camera);
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

void Level::updateAspect() {
    for(int i = 0; i < width/16; i++) {
        for(int j = 0; j < height/16; j++) {
            chunks[i].updateAspect();
        }
    }
}

}