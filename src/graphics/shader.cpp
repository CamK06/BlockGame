#include "shader.h"
#include "../util/log.h"

#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Graphics
{

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    // Initial variables for loading
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertShaderFile;
    std::ifstream fragShaderFile;
    std::stringstream vertShaderStream;
    std::stringstream fragShaderStream;
    
    // Allow exceptions
    vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // Load the shader code
    vertShaderFile.open("res/shaders/" + vertexPath);
    fragShaderFile.open("res/shaders/" + fragmentPath);
    vertShaderStream << vertShaderFile.rdbuf();
    fragShaderStream << fragShaderFile.rdbuf();
    vertShaderFile.close();
    fragShaderFile.close();

    // Convert streams into strings of code
    vertexCode = vertShaderStream.str();
    fragmentCode = fragShaderStream.str();
    const char* vertShaderCode = vertexCode.c_str();
    const char* fragShaderCode = fragmentCode.c_str();

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
        Log::write("VERTEX SHADER COMPILATION FAILED!");
        Log::write(infoLog);
    }

    // Compile the fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShaderCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succeeded);
    if(!succeeded) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        Log::write("FRAGMENT SHADER COMPILATION FAILED!");
        Log::write(infoLog);
    }

    // Create the shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &succeeded);
    if(!succeeded) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        Log::write("SHADER LINKING FAILED!");
        Log::write(infoLog);
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