#pragma once
#include "Object.h"
#include "StaticMesh.h"
#include "Shader.h"

class Mesh: public Object
{
public:
    std::vector<StaticMesh*> m_static_meshes = {nullptr};
    Shader* m_shader = nullptr;
    
private:
    glm::mat4  m_transMat;
    
public:
    Mesh(Transform transform, std::vector<StaticMesh*> static_meshes, Shader* shader);
    Mesh(Transform transform, StaticMesh* static_mesh, Shader* shader);
    
    void Draw();
};
