#pragma once

#include "../../Mesh.h"

class Sphere : public Mesh
{
private:
    const float gr = (1.0f + sqrt(5.0f)) * 0.5f;
    const float a = 1.0f;
    const float b = 1.0f / gr;
    
    std::vector<float> m_vertices = {
        0, b, -a,
        b, a, 0,
        -b, a, 0,
        0, b, a,
        0, -b, a,
        -a, 0, b,
        0, -b, -a,
        a, 0, -b,
        a, 0, b,
        -a, 0, -b,
        b, -a, 0,
        -b, -a, 0,
        
    };
    std::vector<int>   m_indices = {
        2, 1, 0,
        1, 2, 3,
        5, 4, 3,
        4, 8, 3,
        7, 6, 0,
        6, 9, 0,
        11, 10, 4,
        10, 11, 6,
        9, 5, 2,
        5, 9, 11,
        8, 7, 1,
        7, 8, 10,
        2, 5, 3,
        8, 1, 3,
        9, 2, 0,
        1, 7, 0,
        11, 9, 6,
        5, 11, 4,
        10, 8, 4
    };

    void project_to_unit_sphere();

public:
    Sphere()
    {
        InitializeMesh(m_vertices, m_indices);
    }
    Sphere(Transform transform)
    {
        m_transform = transform;
        InitializeMesh(m_vertices, m_indices);
    }
};
