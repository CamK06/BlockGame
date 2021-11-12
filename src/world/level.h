#pragma once

#include "block.h"
#include "../graphics/renderers/blockrenderer.h"

namespace World
{

class Level
{
public:
    Level(int width, int height, int depth);
    bool isSolidBlock(int x, int y, int z);
    bool isBlock(int x, int y, int z);
    void setBlock(int x, int y, int z, int blockType);
    void render(glm::vec3 pos, Graphics::Camera* camera);
    void updateMesh();
    void updateAspect();

private:
    int width, height, depth;
    int* blocks;
};

}