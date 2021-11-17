#include "chunk.h"

namespace World
{

Chunk::Chunk(int x, int z, Level* level)
{
    this->level = level;
    this->x = x;
    this->z = z;
    this->renderer = new Graphics::ChunkRenderer(this, level);
    isDirty = true;
}

void Chunk::render(Graphics::Camera* camera)
{
    if(isDirty) {
        rebuild();
        isDirty = false;
    }

    // We offset the mesh by levelWidth/2-levelWidth (so, negative levelWidth/2) so that 0,0 is the center of the world
    renderer->render(glm::vec3(level->width/2-level->width, 0, level->height/2-level->height), camera);
}

void Chunk::rebuild()
{
    renderer->clearMesh();
    for(int i = 0; i < CHUNK_WIDTH; i++)
        for(int j = 0; j < CHUNK_HEIGHT; j++)
            for(int k = 0; k < CHUNK_DEPTH; k++)
                renderer->addBlockToMesh(i+(x*CHUNK_WIDTH), k, j+(z*CHUNK_HEIGHT), level->getBlock(i+(x*CHUNK_WIDTH), k, j+(z*CHUNK_HEIGHT)));

}

void Chunk::updateAspect() { renderer->updateAspect(); }

}