#pragma once
#include <string>
#include <glm/ext/matrix_float4x4.hpp>

#include "Debugging.h"

class Shader
{
private:
    unsigned int m_shader_program;
    
private:
    std::string LoadShader(const char* aPath);
    unsigned int LoadVertexShader(const char* aPath);
    unsigned int LoadFragmentShader(const char* aPath);
    
public:
    Shader() = default;
    Shader(const std::string& vertex_path, const std::string& fragment_path);
    
    void Initialize(const char* aVertexPath, const char* aFragmentPath);
    void Use();
    
    void SetMatrix4(const std::string& aUniformName, glm::mat4 aMatrix);
    void SetVec3(const std::string& aUniformName, glm::vec3 aColor);
};
