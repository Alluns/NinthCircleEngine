#pragma once
#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

class Camera
{
public:
    glm::vec3 m_camera_position = {0, 0, 5.0f};
    glm::vec3 m_camera_forward  = {0, 0, -1.0f};
    glm::vec3 m_camera_up       = {0, 1.0f, 0};
    
public:
    glm::mat4 GetView();
};
