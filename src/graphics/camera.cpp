#include "camera.h"

namespace Graphics
{

Camera::Camera(glm::vec3 pos)
{
    // Initialize all necessary vectors
    this->pos = pos;
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = -90;
}

void Camera::update()
{
    view = glm::lookAt(pos, pos+front, up);  
}

void Camera::input(GLFWwindow* window, float deltaTime)
{
    // Set the speed of the camera according to deltaTime and the LSHIFT modifier key
    float cameraSpeed = 10.0f * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraSpeed *= 5.0f;
    
    // Check for basic movement keys
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos += cameraSpeed * front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos -= cameraSpeed * front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pos -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        pos += glm::normalize(glm::cross(front, up)) * cameraSpeed;
}

void Camera::mouse(GLFWwindow* window, double xpos, double ypos)
{
    Camera* camera = (Camera*)glfwGetWindowUserPointer(window);

    if(camera->firstMouse) {
        camera->lastX = xpos;
        camera->lastY = ypos;
        camera->firstMouse = false;
    }

    // Calculate offsets
    float xOffset = xpos - camera->lastX;
    float yOffset = camera->lastY - ypos;
    camera->lastX = xpos;
    camera->lastY = ypos;

    // 0.1f is the sensitivity
    xOffset *= 0.1f;
    yOffset *= 0.1f;
    camera->pitch += yOffset;
    camera->yaw += xOffset;

    // Limit the pitch of the camera
    if(camera->pitch > 89.0f)
        camera->pitch = 89.0f;
    if(camera->pitch < -89.0f)
        camera->pitch = -89.0f;

    camera->direction.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
    camera->direction.y = sin(glm::radians(camera->pitch));
    camera->direction.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
    camera->front = glm::normalize(camera->direction);
}

}