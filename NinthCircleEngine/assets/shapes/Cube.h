#pragma once

#include "../../Mesh.h"
#include "../../Transform.h"

class Cube : public Mesh
{
private:
    std::vector<float> m_vertices = {
        -1, -1,  1,
         1, -1,  1,
         1,  1,  1,
        -1,  1,  1,
         1, -1, -1,
        -1, -1, -1,
        -1,  1, -1,
         1,  1, -1
    };
    std::vector<int>   m_indices = {
        0, 1, 2,    // Front
        2, 3, 0,    
        1, 4, 7,    // Right
        7, 2, 1,    
        4, 5, 6,    // Back
        6, 7, 4,
        5, 0, 3,    // Left
        3, 6, 5,
        3, 2, 7,    // Top
        7, 6, 3,
        0, 5, 4,    // Bottom :3c
        4, 1, 0
    };
    
public:
    Cube()
    {
        InitializeMesh(m_vertices, m_indices);
    }
    Cube(Transform transform)
    {
        m_transform = transform;
        InitializeMesh(m_vertices, m_indices);
    }
};