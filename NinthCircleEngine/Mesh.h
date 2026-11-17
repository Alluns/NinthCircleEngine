#pragma once
#include "StaticMesh.h"
#include "Transform.h"
#include "Shader.h"

class Mesh
{
public:
    Transform m_transform = {{0, 0,0 },{0, 0, 0},{1, 1, 1}};
    std::vector<StaticMesh*> m_static_meshes = {nullptr};
    Shader* m_shader = nullptr;
    
private:
    glm::mat4  m_transMat;
    
public:
    Mesh(Transform transform, std::vector<StaticMesh*> static_meshes, Shader* shader);
    Mesh(Transform transform, StaticMesh* static_mesh, Shader* shader);
    
    void Draw();
};
