#pragma once
#include <string>
#include <glm/ext/matrix_float4x4.hpp>

#include "Debugging.h"

class Shader
{
private:
    std::string LoadShader(const char* aPath);
    unsigned int LoadVertexShader(const char* aPath);
    unsigned int LoadFragmentShader(const char* aPath);
    
public:
    unsigned int aShaderProgram;
    
    void Initialize(const char* aVertexPath, const char* aFragmentPath);
    void Use();
    
    void SetMatrix4(const std::string& aUniformName, glm::mat4 aMatrix);
};
