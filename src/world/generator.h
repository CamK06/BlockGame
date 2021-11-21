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
    void GenerateChunk(int x, int z);

private:
    Level* level;
    siv::PerlinNoise noise;
    siv::PerlinNoise noise2;
};

}