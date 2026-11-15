#pragma once
#include <vector>
#include <glm/ext/matrix_float4x4.hpp>

#include "Shader.h"
#include "Transform.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

class StaticMesh
{
public:
    std::string m_name;
    
protected:
    unsigned int m_VBO = 0;
    unsigned int m_VAO = 0;
    unsigned int m_EBO = 0;
    
    unsigned int m_texture = 0;
    
    std::string m_texture_path = "C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Dress.png";
    
private:
    int m_indexCount = 0;
    
public:
    ~StaticMesh();
    
    void InitializeMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    
    void Draw(Shader* aShader, glm::mat4 transMat);
};
