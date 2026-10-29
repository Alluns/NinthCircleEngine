#pragma once
#include <string>

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
};
