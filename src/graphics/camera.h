#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Graphics
{

class Camera
{
public:
    Camera(glm::vec3 pos);

    void update();
    void input(GLFWwindow *window, float deltaTime);
    static void mouse(GLFWwindow* window, double xpos, double ypos);

    glm::mat4 view;
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 direction;
    
    float lastX;
    float lastY;
    float pitch;
    float yaw;
private:
};

}