#pragma once

#include "block.h"
#include "chunk.h"
#include "generator.h"

#include <vector>

namespace World
{

class Chunk;
class Generator;

class Level
{
public:
    Level(int width, int height, int depth);
    Chunk* getChunk(int x, int z);
    bool isSolidBlock(int x, int y, int z);
    bool isBlock(int x, int y, int z);
    void setBlock(int x, int y, int z, int blockType);
    int getBlock(int x, int y, int z);
    void render(Graphics::Camera* camera);
    void updateAspect();
    void update();

    int width, height, depth;
    Generator* worldGen;

private:
    Chunk* chunks;
    int* blocks;
};

}