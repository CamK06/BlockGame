#include "mesh.h"

namespace Graphics 
{

void Mesh::addVertex(float x, float y, float z)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
    if(hasTexture) {
        vertices.push_back(u);
        vertices.push_back(v);
    }
    vertices.push_back(brightness);
}

void Mesh::setBrightness(float brightness)
{
    this->brightness = brightness;
}

void Mesh::addTexture(float u, float v)
{
    this->u = u;
    this->v = v;
    hasTexture = true;
}

int Mesh::getNumVertices()
{
    return vertices.size();
}

void Mesh::clear()
{
    vertices.clear();
    hasTexture = false;
    brightness = 1.0f;
}

float* Mesh::getVertices()
{
    return vertices.data();
}

}