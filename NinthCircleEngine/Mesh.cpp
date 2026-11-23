#include "Mesh.h"

Mesh::Mesh(const Transform& transform, const std::vector<StaticMesh*>& static_meshes, Shader* shader)
{
    SetTransform(transform);
    m_static_meshes = static_meshes;
    m_shader = shader;
}

Mesh::Mesh(const Transform& transform, StaticMesh* static_mesh, Shader* shader)
{
    SetTransform(transform);
    m_static_meshes = {static_mesh};
    m_shader = shader;
}

void Mesh::Draw()
{
    m_transMat = GetTransform().To4xMatrix();
    
    for (StaticMesh*& static_mesh : m_static_meshes)
    {
        static_mesh->Draw(m_shader, m_transMat);
    }
}
