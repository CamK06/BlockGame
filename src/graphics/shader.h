#pragma once

#include <string>

namespace Graphics
{

class Shader
{
public:
    Shader(std::string vertexPath, std::string fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;

    unsigned int ID;

private:
};

}