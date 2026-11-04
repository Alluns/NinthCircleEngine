#pragma once

#include "../../Mesh.h"

class Pyramid : public Mesh
{
private:
    std::vector<float> m_vertices = {
        -1, -1,  1,
         1, -1,  1,
         1, -1, -1,
        -1, -1, -1,
         0,  1,  0 
        
    };
    std::vector<int>   m_indices = {
        0, 3, 2,    // Bottom :3c
        2, 1, 0,
        0, 1, 4,    // Front
        1, 2, 4,    // Right
        2, 3, 4,    // Back
        3, 0, 4     // Left
    };
    
public:
    Pyramid()
    {
        InitializeMesh(m_vertices, m_indices);
    }
    Pyramid(Transform transform)
    {
        m_transform = transform;
        InitializeMesh(m_vertices, m_indices);
    }
};
