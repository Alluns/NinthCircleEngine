#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>

glm::mat4 Camera::GetView()
{
    return glm::lookAt(m_camera_position, m_camera_position + m_camera_forward, m_camera_up);
}

void Camera::ProcessInput(GLFWwindow* window, float delta_time)
{
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
