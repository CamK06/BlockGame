#include "shader.h"
#include "../util/log.h"

#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Graphics
{

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // Initial variables for loading
    std::ifstream vertShaderFile;
    std::ifstream fragShaderFile;
    std::stringstream vertShaderStream;
    std::stringstream fragShaderStream;
    
    // Allow exceptions
    vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // Load the shader code
    vertShaderFile.open(vertexPath);
    fragShaderFile.open(fragmentPath);
    vertShaderStream << vertShaderFile.rdbuf();
    fragShaderStream << fragShaderFile.rdbuf();
    vertShaderFile.close();
    fragShaderFile.close();

    // Convert streams into strings of code
    const char* vertShaderCode = vertShaderStream.str().c_str();
    const char* fragShaderCode = fragShaderStream.str().c_str();

    // Initial variables for compilation
    unsigned int vertexShader;
    unsigned int fragmentShader;
    int succeeded;
    char infoLog[512];

    // Compile the vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertShaderCode, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succeeded);
    if(!succeeded) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        Util::Log::write("VERTEX SHADER COMPILATION FAILED!");
        Util::Log::write(infoLog);
    }

    // Compile the fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShaderCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succeeded);
    if(!succeeded) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        Util::Log::write("FRAGMENT SHADER COMPILATION FAILED!");
        Util::Log::write(infoLog);
    }

    // Create the shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &succeeded);
    if(!succeeded) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        Util::Log::write("SHADER LINKING FAILED!");
        Util::Log::write(infoLog);
    }
    
    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::use() { glUseProgram(ID); }

}