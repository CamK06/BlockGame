#pragma once

#include "texture.h"

#include <vector>

namespace Graphics
{

class Mesh
{
public:
    void addVertex(float x, float y, float z);
    void addTexture(float u, float v);
    void clear();

    float* getVertices();
    int getNumVertices();

private:
    float u, v;
    bool hasTexture;

    std::vector<float> vertices;
};

}