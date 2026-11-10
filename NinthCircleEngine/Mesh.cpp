#include "Mesh.h"

Mesh::Mesh(Transform transform, StaticMesh* mesh, Shader* shader)
{
    m_transform = transform;
    m_staticMesh = mesh;
    m_shader = shader;
}

void Mesh::Draw()
{
    m_transMat = m_transform.To4xMatrix();
    m_staticMesh->Draw(m_shader, m_transMat);
}
