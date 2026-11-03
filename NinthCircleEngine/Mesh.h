#pragma once
#include <vector>
#include <glm/ext/matrix_float4x4.hpp>

#include "Shader.h"

class Mesh
{
private:
    int m_indexCount = 0;
    
protected:
    unsigned int m_VBO;
    unsigned int m_VAO;
    unsigned int m_EBO;
    
    glm::mat4 m_transform = glm::mat4(1.0f);
    glm::mat4 m_view = glm::mat4(1.0f);
    glm::mat4 m_projection = glm::mat4(1.0f);
    
public:
    Mesh(const std::vector<float>& vertices, const std::vector<int>& indices);
    ~Mesh();
    
    void Draw(Shader* aShader);
};
