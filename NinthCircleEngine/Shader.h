#pragma once
#include <string>
#include <glm/ext/matrix_float4x4.hpp>

#include "Debugging.h"

class Shader
{
private:
    unsigned int m_shader_program;
    
private:
    std::string LoadShader(const char* path);
    unsigned int LoadVertexShader(const char* path);
    unsigned int LoadFragmentShader(const char* path);
    
public:
    Shader() = default;
    Shader(const std::string& vertex_path, const std::string& fragment_path);
    
    void Initialize(const char* vertex_path, const char* fragment_path);
    void Use();
    
    void SetMatrix4(const std::string& uniform_name, glm::mat4 matrix);
    void SetVec3(const std::string& uniform_name, glm::vec3 color);
};
