#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>

std::string Shader::LoadShader(const char* aPath)
{
    std::string shaderCode;
    std::ifstream shaderFile;
    
    shaderFile.open(aPath);
    
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    
    shaderFile.close();
    shaderCode = shaderStream.str();
    
    return shaderCode;
}

unsigned int Shader::LoadVertexShader(const char* aPath)
{
    int result;
    char log[512];
    
    std::string shaderCodeString = LoadShader(aPath);
    const char* shaderCode = shaderCodeString.c_str();
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexShader, 1, &shaderCode, NULL);
    glCompileShader(vertexShader);
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, log);
        std::cout << "Failed to compile vertex shader \n" << log << '\n';
    }
    
    return vertexShader;
}

unsigned int Shader::LoadFragmentShader(const char* aPath)
{
    int result;
    char log[512];
    
    std::string shaderCodeString = LoadShader(aPath);
    const char* shaderCode = shaderCodeString.c_str();
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(fragmentShader, 1, &shaderCode, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, log);
        std::cout << "Failed to compile fragment shader \n" << log << '\n';
    }
    
    return fragmentShader;
}

void Shader::Initialize(const char* aVertexPath, const char* aFragmentPath)
{
    int result;
    char log[512];
    
    unsigned int vertexShader = LoadVertexShader(aVertexPath);
    unsigned int fragmentShader = LoadFragmentShader(aFragmentPath);
    
    aShaderProgram = glCreateProgram();
    
    glAttachShader(aShaderProgram, vertexShader);
    glAttachShader(aShaderProgram, fragmentShader);
    glLinkProgram(aShaderProgram);
    
    glGetProgramiv(aShaderProgram, GL_LINK_STATUS, &result);
    
    if (!result)
    {
        glGetProgramInfoLog(aShaderProgram, 512, NULL, log);
        std::cout << "Shader program failed to compile\n" << log << '\n';
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Use()
{
    glUseProgram(aShaderProgram);
}
