#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "../shader.h"
#include "../texture.h"
#include "../camera.h"
#include "../mesh.h"
#include "../../world/block.h"
#include "../../world/chunk.h"
#include "../../world/level.h"

namespace World {
    class Chunk;
    class Level;
}

namespace Graphics
{

class ChunkRenderer
{
public:
    ChunkRenderer(World::Chunk* chunk, World::Level* level);
    void updateAspect();
    void addBlockToMesh(int x, int y, int z, int blockType);
    void render(glm::vec3 pos, Camera* camera);
    void clearMesh();

private:
    glm::mat4 projection;

    World::Chunk* chunk;
    World::Level* level;
    Shader* shader;
    Texture* textureAtlas;
    Mesh mesh;

    GLFWwindow* window;
    int windowWidth;
    int windowHeight;

    unsigned int VAO;
    unsigned int VBO;
};

}
