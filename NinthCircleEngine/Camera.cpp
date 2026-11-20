#include "Camera.h"

#include <algorithm>
#include <glm/ext/matrix_transform.hpp>

glm::mat4 Camera::GetView()
{
    return glm::lookAt(m_camera_position, m_camera_position + m_camera_forward, m_camera_up);
}

void Camera::Update(glm::dvec2 delta, glm::vec3 direction, float delta_time)
{
    // ROTATION
    delta *= m_camera_sensitivity;
    
    yaw   += delta.x;
    pitch -= delta.y;
    
    pitch = std::clamp(pitch, -89.0f, 89.0f);
    
    glm::vec3 mouse_direction;
    mouse_direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    mouse_direction.y = sin(glm::radians(pitch));
    mouse_direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_camera_forward = glm::normalize(mouse_direction);
    
    m_camera_right = glm::normalize(glm::cross(m_camera_forward, m_camera_up));

    
    // MOVEMENT
    m_camera_position += (direction.x * m_camera_forward + direction.y * m_camera_up + direction.z * m_camera_right) * m_camera_speed * delta_time;
}
