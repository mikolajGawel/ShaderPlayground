#pragma once
#pragma once
#include <GL/glew.h>
#include <iostream>

class Shader
{
private:
    std::string vertexShaderSouce, fragmentShaderSource;
    bool s_created = false;
public:
    unsigned int program;
    Shader(std::string vertexShaderSource, std::string fragmentShaderSource);
    ~Shader();
    void createShader();
    void setUniform2f(const char* uniform_name, float x, float y);
    void setUniform3f(const char* uniform_name, float x, float y, float z);
    void bind();
    void unbind();
};

