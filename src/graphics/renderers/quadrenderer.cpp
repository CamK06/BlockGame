#include "quadrenderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Graphics
{

QuadRenderer::QuadRenderer()
{
    shader = new Shader("shaders/basic.vs", "shaders/basic.fs");
    vertexes = new float[12] {
        -0.5,  0.5, 0,
         0.5,  0.5, 0,
         0.5, -0.5, 0,
        -0.5, -0.5, 0,
    };
    
}

void QuadRenderer::render()
{
    shader->use();
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexes);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

}