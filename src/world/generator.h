#pragma once

#include "level.h"
#include "../util/perlin.hpp"

namespace World
{

class Level;

class Generator
{
public:
    Generator(Level* level);
    void generateChunk(int x, int z);

private:
    Level* level;
    siv::PerlinNoise noise;
    siv::PerlinNoise noise2;
};

}