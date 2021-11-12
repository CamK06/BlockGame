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
    void setBrightness(float brightness);
    void clear();

    float* getVertices();
    int getNumVertices();

private:
    float u, v;
    float brightness = 1.0;
    bool hasTexture;

    std::vector<float> vertices;
};

}