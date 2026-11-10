#pragma once
#include "StaticMesh.h"
#include "Transform.h"
#include "Shader.h"

class Mesh
{
public:
    Transform m_transform = {{0, 0,0 },{0, 0, 0},{1, 1, 1}};
    StaticMesh* m_staticMesh = nullptr;
    Shader* m_shader = nullptr;
    
private:
    glm::mat4  m_transMat;
    glm::mat4* m_viewMat;
    glm::mat4* m_projMat;
    
public:
    Mesh(Transform transform, StaticMesh* mesh, Shader* shader);
    
    void Draw();
};
