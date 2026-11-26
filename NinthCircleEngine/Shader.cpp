#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

std::string Shader::LoadShader(const char* path)
{
    std::string shaderCode;
    std::ifstream shaderFile;
    
    shaderFile.open(path);
    
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    
    shaderFile.close();
    shaderCode = shaderStream.str();
    
    return shaderCode;
}

unsigned int Shader::LoadVertexShader(const char* path)
{
    int result;
    char log[512];
    
    std::string shaderCodeString = LoadShader(path);
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
    
    glCheckError();
    
    return vertexShader;
}

unsigned int Shader::LoadFragmentShader(const char* path)
{
    int result;
    char log[512];
    
    std::string shaderCodeString = LoadShader(path);
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
    
    glCheckError();
    
    return fragmentShader;
}

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path)
{
    Initialize(vertex_path.c_str(), fragment_path.c_str());
}

void Shader::Initialize(const char* vertex_path, const char* fragment_path)
{
    int result;
    char log[512];
    
    unsigned int vertex_shader = LoadVertexShader(vertex_path);
    unsigned int fragment_shader = LoadFragmentShader(fragment_path);
    
    m_shader_program = glCreateProgram();
    
    glAttachShader(m_shader_program, vertex_shader);
    glAttachShader(m_shader_program, fragment_shader);
    glLinkProgram(m_shader_program);
    
    glGetProgramiv(m_shader_program, GL_LINK_STATUS, &result);
    
    if (!result)
    {
        glGetProgramInfoLog(m_shader_program, 512, NULL, log);
        std::cout << "Shader program failed to compile\n" << log << '\n';
    }
    
    glDetachShader(m_shader_program, vertex_shader);
    glDetachShader(m_shader_program, fragment_shader);
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    glCheckError();
}

void Shader::Use()
{
    glUseProgram(m_shader_program);
    
    glCheckError();
}

void Shader::SetMatrix4(const std::string& uniform_name, glm::mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(m_shader_program, uniform_name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetVec3(const std::string& aUniformName, glm::vec3 aColor)
{
    glUniform3f(glGetUniformLocation(m_shader_program, aUniformName.c_str()), aColor.r, aColor.g, aColor.b);
}
