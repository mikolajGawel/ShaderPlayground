#include "Shader.hpp"
#include <string>
#include <sstream>
#include <fstream>
static void _createShader(GLuint& shader, int shaderType, std::string shaderSource)
{
    std::cout << shaderSource;
    const char* shrSrc = shaderSource.c_str();
    int result;
    shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &shrSrc, 0);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int lenght = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &lenght);
        char* log = (char*)malloc(sizeof(char) * lenght);
        glGetShaderInfoLog(shader, lenght, &lenght, log);
        std::cout << (shaderType == GL_VERTEX_SHADER ? "Vertex" : (shaderType == GL_FRAGMENT_SHADER ? "Fragment" : "Unkown Shader type")) << " Shader Error:\n" << log << "\n";
    }
}
static std::string loadStringFromFile(std::string file_path)
{
    std::string line;
    std::stringstream ss;
    std::ifstream file;
    file.open(file_path);

    while (getline(file, line))
    {
        ss << line << "\n";
    }

    file.close();
    return ss.str();
}
Shader::Shader(std::string vertexShaderSource, std::string fragmentShaderSource) :
    vertexShaderSouce(vertexShaderSource), fragmentShaderSource(fragmentShaderSource)
{
    program = 0;
}
Shader::~Shader()
{
    if (program == NULL)return;
    glDeleteShader(program);
}
void Shader::createShader() {
    const char* vertSrc = vertexShaderSouce.c_str();
    int result;
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertSrc, 0);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int lenght = 0;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &lenght);
        char* log = (char*)malloc(sizeof(char) * lenght);
        glGetShaderInfoLog(vertex, lenght, &lenght, log);
        std::cout << "Vertex " << " Shader Error:\n" << log << "\n";
    }
    const char* fragSrc = fragmentShaderSource.c_str();

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragSrc, 0);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int lenght = 0;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &lenght);
        char* log = (char*)malloc(sizeof(char) * lenght);
        glGetShaderInfoLog(fragment, lenght, &lenght, log);
        std::cout << "Vertex " << " Shader Error:\n" << log << "\n";
    }

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    s_created = true;
    unbind();
}
void Shader::bind()
{
    if (!s_created)createShader();
    glUseProgram(program);
}
void Shader::unbind()
{
    glUseProgram(0);
}
void Shader::setUniform2f(const char* uniform_name, float x, float y)
{
    bind();
    int location = glGetUniformLocation(program, uniform_name);
    glUniform2f(location, x, y);
}
void Shader::setUniform3f(const char* uniform_name, float x, float y, float z)
{
    bind();
    int location = glGetUniformLocation(program, uniform_name);
    glUniform3f(location, x, y, z);
}