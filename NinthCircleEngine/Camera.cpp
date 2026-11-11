#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>

glm::mat4 Camera::GetView()
{
    return glm::lookAt(m_camera_position, m_camera_position + m_camera_forward, m_camera_up);
}
