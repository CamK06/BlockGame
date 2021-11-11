#include "mesh.h"

namespace Graphics 
{

Mesh::Mesh()
    : texture("textures/terrain.png")
{}

void Mesh::addVertex(float x, float y, float z)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
    if(hasTexture) {
        vertices.push_back(u);
        vertices.push_back(v);
    }
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
}

float* Mesh::getVertices()
{
    return vertices.data();
}

}