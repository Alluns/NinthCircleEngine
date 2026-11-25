#include "Camera.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "InputManager.h"

Camera::Camera()
{
    glfwGetWindowSize(glfwGetCurrentContext(), &m_width, &m_height);
}

Camera::Camera(const int width, const int height)
{
    m_width = width;
    m_height = height;
}

glm::mat4 Camera::GetView()
{
    return glm::lookAt(GetPosition(), GetPosition() + Forward(), Up());
}

glm::mat4 Camera::GetProjection()
{
    if (m_is_orthographic) { return glm::ortho(-AspectRatio(), AspectRatio(), -1.0f, 1.0f, 0.1f, 100.0f); }
    
    return glm::perspective(glm::radians(45.0f), AspectRatio(), 0.1f, 100.0f);
}

void Camera::Update(const float delta_time)
{
    Object::Update(delta_time);
    
    if (InputManager::GetInstance()->IsKeyJustPressed(GLFW_KEY_F4))
        SetIsOrthographic(!m_is_orthographic);
}
