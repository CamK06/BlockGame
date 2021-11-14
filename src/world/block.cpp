#include "block.h"
#include "../graphics/texture.h"

#include <map>

namespace World
{

std::vector<Block> Block::blocks;

Block::Block(int textureID)
{
    // Initialize all faces to the given texture ID
    for(int i = 0; i < 6; i++) {
        setFaceTex((BlockFace)i, textureID);
    }
    this->baseTexID = textureID;

    init();
}

void Block::setFaceTex(BlockFace face, int textureID)
{
    // Calculate UV coordinates
    // TODO: Allow different size texture atlases
    float u = textureID / 16.0f;
    float u1 = u + 0.0624375f;
    float v = 0.0f; // TODO: Update this value once more textures are added, to allow for another row
    float v1 = v + 0.0624375f;
    
    uvs[face].u = u1;
    uvs[face].v = v1;
    uvs[face].textureID = textureID;
}

void Block::initBlocks()
{
    // Initialize all blocks here
    // TODO: Find a cleaner way of doing face textures (Possibly do face groups)
    Block grass(0);
    grass.setFaceTex(BlockFace::Front, 1);
    grass.setFaceTex(BlockFace::Right, 1);
    grass.setFaceTex(BlockFace::Back, 1);
    grass.setFaceTex(BlockFace::Left, 1);
    grass.setFaceTex(BlockFace::Down, 2);

    Block dirt(2);
    Block stone(3);

    // Add all blocks *IN ORDER!*
    blocks.push_back(grass);
    blocks.push_back(dirt);
    blocks.push_back(stone);
}

}