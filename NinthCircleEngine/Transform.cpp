#include "Transform.h"

#include <glm/ext/matrix_transform.hpp>

Transform::Transform()
{
    m_position = {0, 0, 0};
    m_rotation = {0, 0, 0};
    m_scale    = {1, 1, 1};
}

Transform::Transform(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale)
{
    m_position = position;
    m_rotation = rotation;
    m_scale = scale;
}

Transform Transform::operator+(const Transform& other) const
{
    return {
        {this->m_position + other.m_position},
        {this->m_rotation + other.m_rotation},
        {this->m_scale + other.m_scale}
    };
}

glm::mat4 Transform::To4xMatrix()
{
    glm::mat4 matrix = glm::mat4(1.0f);
    
    matrix = glm::translate(matrix, m_position);
    
    matrix = glm::rotate(matrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0,    0));
    matrix = glm::rotate(matrix, glm::radians(m_rotation.y), glm::vec3(0,    1.0f, 0));
    matrix = glm::rotate(matrix, glm::radians(m_rotation.z), glm::vec3(0,    0,    1.0f));
    
    matrix = glm::scale(matrix, m_scale);
    
    return matrix;
}
