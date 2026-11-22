#include "Camera.h"

#include <algorithm>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

glm::mat4 Camera::GetView()
{
    return glm::lookAt(GetPosition(), GetPosition() + m_camera_forward, m_camera_up);
}

glm::mat4 Camera::GetProjection() const
{
    if (m_is_orthographic) { return glm::ortho(-3.0f, 3.0f, -2.0f, 2.0f, 0.1f, 100.0f); }
    
    return glm::perspective(glm::radians(45.0f), 1080.0f/720.0f, 0.1f, 100.0f);
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
    SetPosition(GetPosition() += (direction.x * m_camera_forward + direction.y * m_camera_up + direction.z * m_camera_right) * m_camera_speed * delta_time);
}
