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
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    glm::mat4 To4xMatrix();
};
