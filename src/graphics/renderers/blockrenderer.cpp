#include "blockrenderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../world/block.h"
#include "../../world/level.h"

namespace Graphics
{

CubeRenderer::CubeRenderer()
{
    shader = new Shader("shaders/block.vs", "shaders/block.fs");
    textureAtlas = new Texture("textures/terrain.png");

    // Generate VAO, VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // VAO Setup
    glBindVertexArray(VAO);

    // VBO Setup
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.getNumVertices() * sizeof(float), mesh.getVertices(), GL_STATIC_DRAW);

    // Set position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Set UV attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CubeRenderer::updateMesh(World::Level* level, int x, int y, int z, int blockType)
{
    if(blockType == BLOCK_AIR)
        return;

    // Calculate UV coordinates
    float u = blockType / 16.0f;
    float u1 = u + 0.0624375f;
    float v = 0.0f; // TODO: Update this value once more textures are added, to allow for another row
    float v1 = v + 0.0624375f;

    // Calculate XYZ coordinates
    float x1 = x + 1.0f;
    float y1 = y + 1.0f;
    float z1 = z + 1.0f;

    // Create faces
    if(!level->isSolidBlock(x, y - 1, z)) { // Bottom
        mesh.addTexture(u, v1);
        mesh.addVertex(x, y, z1);
        mesh.addTexture(u, v);
        mesh.addVertex(x, y, z);
        mesh.addTexture(u1, v);
        mesh.addVertex(x1, y, z);
        mesh.addTexture(u1, v1);
        mesh.addVertex(x1, y, z1);
    }
    if(!level->isSolidBlock(x, y + 1, z)) { // Top
        mesh.addTexture(u1, v1);
        mesh.addVertex(x1, y1, z1);
        mesh.addTexture(u1, v);
        mesh.addVertex(x1, y1, z);
        mesh.addTexture(u, v);
        mesh.addVertex(x, y1, z);
        mesh.addTexture(u, v1);
        mesh.addVertex(x, y1, z1);
    }
    if(!level->isSolidBlock(x, y, z - 1)) { // Left
        mesh.addTexture(u1, v);
        mesh.addVertex(x, y1, z);
        mesh.addTexture(u, v);
        mesh.addVertex(x1, y1, z);
        mesh.addTexture(u, v1);
        mesh.addVertex(x1, y, z);
        mesh.addTexture(u1, v1);
        mesh.addVertex(x, y, z);
    }
    if(!level->isSolidBlock(x, y, z + 1)) { // Right
        mesh.addTexture(u, v);
        mesh.addVertex(x, y1, z1);
        mesh.addTexture(u, v1);
        mesh.addVertex(x, y, z1);
        mesh.addTexture(u1, v1);
        mesh.addVertex(x1, y, z1);
        mesh.addTexture(u1, v);
        mesh.addVertex(x1, y1, z1);
    }
    if(!level->isSolidBlock(x - 1, y, z)) { // Front
        mesh.addTexture(u1, v);
        mesh.addVertex(x, y1, z1);
        mesh.addTexture(u, v);
        mesh.addVertex(x, y1, z);
        mesh.addTexture(u, v1);
        mesh.addVertex(x, y, z);
        mesh.addTexture(u1, v1);
        mesh.addVertex(x, y, z1);
    }
    if(!level->isSolidBlock(x + 1, y, z)) { // Back
        mesh.addTexture(u, v1);
        mesh.addVertex(x1, y, z1);
        mesh.addTexture(u1, v1);
        mesh.addVertex(x1, y, z);
        mesh.addTexture(u1, v);
        mesh.addVertex(x1, y1, z);
        mesh.addTexture(u, v);
        mesh.addVertex(x1, y1, z1);
    }
}

void CubeRenderer::render(glm::vec3 pos, Camera* camera)
{
    // TODO: Move this VBO updating to a better location
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.getNumVertices() * sizeof(float), mesh.getVertices(), GL_STATIC_DRAW);

    shader->use();
    textureAtlas->use();

    // Model
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    model = glm::translate(model, pos);

    // View
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // Projection
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(70.0f), 1280.0f / 720.0f, 0.1f, 500.0f);

    unsigned int modelLoc = glGetUniformLocation(shader->ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    unsigned int viewLoc = glGetUniformLocation(shader->ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->view));
    unsigned int projectionLoc = glGetUniformLocation(shader->ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawArrays(GL_QUADS, 0, mesh.getNumVertices());
}

}