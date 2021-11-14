#include "../graphics/renderers/blockrenderer.h"
#include "level.h"
#include "block.h"

namespace World
{

Graphics::CubeRenderer* renderer;

Level::Level(int width, int height, int depth)
{
    this->width = width;
    this->height = height;
    this->depth = depth;
    blocks = new int[width*height*depth];
    for(int i = 0; i < width*height*depth; i++)
        blocks[i] = BLOCK_AIR;
    renderer = new Graphics::CubeRenderer();
}

void Level::setBlock(int x, int y, int z, int blockType)
{
    // Return if the block is outside of the level
    if(x < 0 || y < 0 || z < 0 || x >= width || y >= depth || z >= height)
        return;

    blocks[(y * height + z) * width + x] = blockType;
}

void Level::updateMesh()
{
    renderer->mesh.clear();
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            for(int k = 0; k < depth; k++) {
                renderer->updateMesh(this, i, k, j, blocks[(k * height + j) * width + i]);
            }
        }
    }
}

bool Level::isBlock(int x, int y, int z)
{
    // Check if the block is outside of the level
    if(x < 0 || y < 0 || z < 0 || x >= width || y >= depth || z >= height)
        return false;

    // TODO: Change this to a block transparency check
    return blocks[(y * height + z) * width + x] != BLOCK_AIR;
}

bool Level::isSolidBlock(int x, int y, int z)
{
    return isBlock(x, y, z);
}

void Level::render(glm::vec3 pos, Graphics::Camera* camera)
{
    renderer->render(pos, camera);
}

void Level::updateAspect() {
    renderer->updateAspect();
}

}