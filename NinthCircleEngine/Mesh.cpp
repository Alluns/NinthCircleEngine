#include "Mesh.h"

Mesh::Mesh(Transform transform, StaticMesh* mesh, Shader* shader)
{
    m_transform = transform;
    m_static_meshes = {mesh};
    m_shader = shader;
}

Mesh::Mesh(Transform transform, std::vector<StaticMesh*> static_meshes, Shader* shader)
{
    m_transform = transform;
    m_static_meshes = static_meshes;
    m_shader = shader;
}

void Mesh::Draw()
{
    m_transMat = m_transform.To4xMatrix();
    for (StaticMesh*& static_mesh : m_static_meshes)
    {
        static_mesh->Draw(m_shader, m_transMat);
    }
}
