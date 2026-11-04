#pragma once

#include "../../Mesh.h"

class Sphere : public Mesh
{
private:
    std::vector<float> m_vertices = {};
    std::vector<int>   m_indices = {};

protected:
    void GenerateSphere(int rings, int slices);
    
public:
    Sphere()
    {
        GenerateSphere(9, 16);
        InitializeMesh(m_vertices, m_indices);
    }
    Sphere(Transform transform)
    {
        GenerateSphere(9, 16);
        m_transform = transform;
        InitializeMesh(m_vertices, m_indices);
    }
};
