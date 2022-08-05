#include "generator.h"
#include "level.h"

namespace World
{

Generator::Generator(Level* level)
{
    this->level = level;
    noise.reseed(time(0)*rand());
    noise2.reseed(rand());
}

void Generator::generateChunk(int x, int z)
{
    for(int i = 0; i < 16+(x*16); i++) {
        for(int j = 0; j < 16+(z*16); j++) {
            
            int genHeight = 64 + noise.accumulatedOctaveNoise2D(i/100.0f, j/100.0f, 2) + noise.normalizedOctaveNoise2D(i/100.0f, j/100.0f, 4) * 32;
            for(int k = 0; k < genHeight; k++) {

                if(k == genHeight-1) // Generate grass on the top layer
                    level->setBlock(i, k, j, BLOCK_GRASS);
                else if(k >= genHeight-4) // Generate dirt if we're in the top 3 blocks under the grass
                    level->setBlock(i, k, j, BLOCK_DIRT);
                else // Otherwise generate stone
                    level->setBlock(i, k, j, BLOCK_STONE);
            }
        }
    }
}

}