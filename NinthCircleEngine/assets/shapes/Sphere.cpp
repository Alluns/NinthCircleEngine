#include "Sphere.h"

void Sphere::project_to_unit_sphere()
{
    for (int i = 0; i < m_vertices.size(); i += 3)
    {
        glm::vec3 tri(m_vertices[i], m_vertices[i + 1], m_vertices[i + 2]);
        
        normalize(tri);
        
        m_vertices[i] = tri.x;
        m_vertices[i + 1] = tri.y;
        m_vertices[i + 2] = tri.z;
    }
}
