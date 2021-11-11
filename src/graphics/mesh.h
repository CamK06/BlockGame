#pragma once

#include "texture.h"

#include <vector>

namespace Graphics
{

class Mesh
{
public:
    Mesh();

    void addVertex(float x, float y, float z);
    void addTexture(float u, float v);
    void clear();

    float* getVertices();
    int getNumVertices();
    // float* getUV();

private:
    float u, v;
    bool hasTexture;

    Texture texture;
    std::vector<float> vertices;
    // std::vector<float> texCoords;
};

}