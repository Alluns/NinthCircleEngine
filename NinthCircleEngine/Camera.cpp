#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(int width, int height)
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
