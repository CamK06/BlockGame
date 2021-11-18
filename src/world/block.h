#pragma once

#include "../graphics/texture.h"

#include <map>
#include <vector>

// TODO: Maybe replace this with an enum?
#define BLOCK_AIR 256
#define BLOCK_GRASS 0
#define BLOCK_DIRT 1
#define BLOCK_STONE 2
#define BLOCK_LOG 3
#define BLOCK_LEAVES 4

namespace World
{

enum BlockFace
{
    Front, Back, Left, Right, Up, Down
};

class Block
{
public:
    Block(int textureID);

    virtual void init() {}
    virtual void onBreak() {}

    // UV
    virtual Graphics::UV getUV(BlockFace face) { return uvs[face]; }
    void setFaceTex(BlockFace face, int textureID);

    static void initBlocks();
    static Block getBlock(int ID) { return blocks[ID]; }

private:
    std::map<BlockFace, Graphics::UV> uvs;
    int baseTexID;
    static std::vector<Block> blocks;

};

}