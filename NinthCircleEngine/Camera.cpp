#include "Camera.h"

#include <algorithm>
#include <glm/ext/matrix_transform.hpp>

glm::mat4 Camera::GetView()
{
    return glm::lookAt(m_camera_position, m_camera_position + m_camera_forward, m_camera_up);
}

void Camera::ProcessInput(GLFWwindow* window, float delta_time)
{
    // Rotation
    glm::dvec2 current_position;
    glfwGetCursorPos(window, &current_position.x, &current_position.y);
    
    glm::dvec2 offset = current_position - m_last_position;
    m_last_position = current_position;
    
    offset *= m_camera_sensitivity;
    
    yaw   += offset.x;
    pitch -= offset.y;

    pitch = std::min(pitch, 89.0f);
    pitch = std::max(pitch, -89.0f);
    
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_camera_forward = glm::normalize(direction);

    
    // Movement
    float actual_speed = m_camera_speed * delta_time;
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera_position += actual_speed * m_camera_forward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera_position -= actual_speed * m_camera_forward;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera_position -= glm::normalize(glm::cross(m_camera_forward, m_camera_up)) * actual_speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera_position += glm::normalize(glm::cross(m_camera_forward, m_camera_up)) * actual_speed;
    
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_camera_position += actual_speed * m_camera_up;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        m_camera_position -= actual_speed * m_camera_up;
}
