#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "../shader.h"
#include "../texture.h"
#include "../camera.h"
#include "../mesh.h"
#include "../../world/block.h"
#include "../../world/level.h"

namespace Graphics
{

class CubeRenderer
{
public:
    CubeRenderer();
    void updateMesh(World::Level* level, int x, int y, int z, int blockType);
    void render(glm::vec3 pos, Camera* camera);
    void updateAspect();

    Mesh mesh;

private:
    glm::mat4 projection;
    Shader* shader;
    Texture* textureAtlas;
    
    GLFWwindow* window;
    int windowWidth, windowHeight;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

}