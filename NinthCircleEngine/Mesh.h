#pragma once
#include <vector>
#include <glm/ext/matrix_float4x4.hpp>

#include "Shader.h"
#include "Transform.h"

class Mesh
{
public:
    Transform m_transform = {{0, 0,0 },{0, 0, 0},{1, 1, 1}};
    
protected:
    unsigned int m_VBO = 0;
    unsigned int m_VAO = 0;
    unsigned int m_EBO = 0;
    
    glm::mat4 m_view = glm::mat4(1.0f);
    glm::mat4 m_projection = glm::mat4(1.0f);
    
private:
    int m_indexCount = 0;
    
    
public:
    ~Mesh();
    
    void InitializeMesh(const std::vector<float>& vertices, const std::vector<int>& indices);
    
    void Draw(Shader* aShader);
};
