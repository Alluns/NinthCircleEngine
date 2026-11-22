#pragma once
#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>


class Transform
{
public:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    
public:
    Transform();
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    
    Transform operator+(const Transform& other) const;

    static Transform zero() { return {{0, 0, 0}, {0, 0, 0}, {1, 1, 1}}; }

    glm::mat4 To4xMatrix();
};
