#include "chunkrenderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Graphics
{

ChunkRenderer::ChunkRenderer(World::Chunk* chunk, World::Level* level)
{
    this->chunk = chunk;
    this->level = level;
    shader = new Shader("block.vs", "block.fs");
    textureAtlas = new Texture("terrain.png");

    // Generate VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // VAO/VBO setup
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.getNumVertices() * sizeof(float), mesh.getVertices(), GL_STATIC_DRAW);

    // Set position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Set UV attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Set brightness attribute
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Set the projection aspect ratio
    window = glfwGetCurrentContext();
    updateAspect();
}

void ChunkRenderer::addBlockToMesh(int x, int y, int z, int blockType)
{
    if(blockType == BLOCK_AIR)
        return;

    World::Block block = World::Block::getBlock(blockType);

    // Calculate UV coordinates
    float u;
    float v = 0.0f; // TODO: Update this value once more textures are added, to allow for another row
    UV uv;

    // Calculate XYZ coordinates
    float x1 = x + 1.0f;
    float y1 = y + 1.0f;
    float z1 = z + 1.0f;

    // Create faces
    if(!level->isSolidBlock(x, y - 1, z)) { // Bottom
        uv = block.getUV(World::BlockFace::Down);
        u = uv.textureID / 16.0f;
        mesh.setBrightness(0.6f);
        mesh.addTexture(u, uv.v);
        mesh.addVertex(x, y, z1);
        mesh.addTexture(u, v);
        mesh.addVertex(x, y, z);
        mesh.addTexture(uv.u, v);
        mesh.addVertex(x1, y, z);
        mesh.addTexture(uv.u, uv.v);
        mesh.addVertex(x1, y, z1);
    }
    if(!level->isSolidBlock(x, y + 1, z)) { // Top
        uv = block.getUV(World::BlockFace::Up);
        u = uv.textureID / 16.0f;
        mesh.setBrightness(1.0f);
        mesh.addTexture(uv.u, uv.v);
        mesh.addVertex(x1, y1, z1);
        mesh.addTexture(uv.u, v);
        mesh.addVertex(x1, y1, z);
        mesh.addTexture(u, v);
        mesh.addVertex(x, y1, z);
        mesh.addTexture(u, uv.v);
        mesh.addVertex(x, y1, z1);
    }
    if(!level->isSolidBlock(x, y, z - 1)) { // Left
        uv = block.getUV(World::BlockFace::Left);
        u = uv.textureID / 16.0f;
        mesh.setBrightness(0.8f);
        mesh.addTexture(uv.u, v);
        mesh.addVertex(x, y1, z);
        mesh.addTexture(u, v);
        mesh.addVertex(x1, y1, z);
        mesh.addTexture(u, uv.v);
        mesh.addVertex(x1, y, z);
        mesh.addTexture(uv.u, uv.v);
        mesh.addVertex(x, y, z);
    }
    if(!level->isSolidBlock(x, y, z + 1)) { // Right
        uv = block.getUV(World::BlockFace::Right);
        u = uv.textureID / 16.0f;
        mesh.setBrightness(0.8f);
        mesh.addTexture(u, v);
        mesh.addVertex(x, y1, z1);
        mesh.addTexture(u, uv.v);
        mesh.addVertex(x, y, z1);
        mesh.addTexture(uv.u, uv.v);
        mesh.addVertex(x1, y, z1);
        mesh.addTexture(uv.u, v);
        mesh.addVertex(x1, y1, z1);
    }
    if(!level->isSolidBlock(x - 1, y, z)) { // Front
        uv = block.getUV(World::BlockFace::Front);
        u = uv.textureID / 16.0f;
        mesh.setBrightness(0.86f);
        mesh.addTexture(uv.u, v);
        mesh.addVertex(x, y1, z1);
        mesh.addTexture(u, v);
        mesh.addVertex(x, y1, z);
        mesh.addTexture(u, uv.v);
        mesh.addVertex(x, y, z);
        mesh.addTexture(uv.u, uv.v);
        mesh.addVertex(x, y, z1);
    }
    if(!level->isSolidBlock(x + 1, y, z)) { // Back
        uv = block.getUV(World::BlockFace::Back);
        u = uv.textureID / 16.0f;
        mesh.setBrightness(0.86f);
        mesh.addTexture(u, uv.v);
        mesh.addVertex(x1, y, z1);
        mesh.addTexture(uv.u, uv.v);
        mesh.addVertex(x1, y, z);
        mesh.addTexture(uv.u, v);
        mesh.addVertex(x1, y1, z);
        mesh.addTexture(u, v);
        mesh.addVertex(x1, y1, z1);
    }
}

void ChunkRenderer::render(glm::vec3 pos, Camera* camera)
{
    if(mesh.getNumVertices() <= 0)
        return;

    // TODO: Move this VBO updating to a better location
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.getNumVertices() * sizeof(float), mesh.getVertices(), GL_DYNAMIC_DRAW);

    shader->use();
    textureAtlas->use();

    // Model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);

    unsigned int renderDistLoc = glGetUniformLocation(shader->ID, "renderDistance");
    glUniform1i(renderDistLoc, level->renderDistance);
    unsigned int modelLoc = glGetUniformLocation(shader->ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    unsigned int viewLoc = glGetUniformLocation(shader->ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->view));
    unsigned int projectionLoc = glGetUniformLocation(shader->ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawArrays(GL_QUADS, 0, mesh.getNumVertices());
}

void ChunkRenderer::updateAspect()
{
    if(window) {
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        projection = glm::perspective(glm::radians(70.0f), (float)windowWidth / windowHeight, 0.1f, 500.0f);
    }
}

void ChunkRenderer::clearMesh() { mesh.clear(); }

}