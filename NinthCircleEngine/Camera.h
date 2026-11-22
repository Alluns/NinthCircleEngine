#pragma once
#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include "Object.h"

class Camera : Object
{
protected:
    glm::vec3 m_camera_forward  = {0, 0, -1.0f};
    glm::vec3 m_camera_up       = {0, 1.0f, 0};
    glm::vec3 m_camera_right    = {1.0f, 0, 0};
    
    float pitch = 0.0f;
    float yaw = -90.0f;
    
    bool m_is_orthographic = false;
    
    const float m_camera_speed = 12.0f;
    const float m_camera_sensitivity = 0.1f;
    
public:
    glm::mat4 GetView();
    glm::mat4 GetProjection() const;
    
    void SetIsOrthographic(const bool value) { m_is_orthographic = value; }
    bool IsOrthographic() const { return m_is_orthographic; }
    
    void Update(glm::dvec2 delta, glm::vec3 direction, float delta_time);
};
