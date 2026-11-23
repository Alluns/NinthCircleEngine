#include "PlayerController.h"

#include <algorithm>
#include <glm/trigonometric.hpp>

PlayerController::PlayerController(InputManager* input_manager)
{
    m_input_manager = input_manager;
}

void PlayerController::Update(const float delta_time)
{
    if (!m_input_manager->IsFocused()) { return; }
    
    Object* root_parent = GetRootParent();
    
    
    // ROTATION
    glm::dvec2 delta = m_input_manager->GetMouseDelta();
    
    delta *= m_mouse_sensitivity;
    
    yaw   += delta.x;
    pitch -= delta.y;
    
    pitch = std::clamp(pitch, -89.0f, 89.0f);
    
    glm::vec3 mouse_direction;
    mouse_direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    mouse_direction.y = sin(glm::radians(pitch));
    mouse_direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    root_parent->SetForward(glm::normalize(mouse_direction));
    root_parent->SetRight(glm::normalize(glm::cross(root_parent->Forward(), root_parent->Up())));
    
    
    // POSITION
    glm::vec3 input_direction = {
        m_input_manager->IsKeyPressed(GLFW_KEY_W) - m_input_manager->IsKeyPressed(GLFW_KEY_S),
        m_input_manager->IsKeyPressed(GLFW_KEY_SPACE) - m_input_manager->IsKeyPressed(GLFW_KEY_LEFT_CONTROL),
        m_input_manager->IsKeyPressed(GLFW_KEY_D) - m_input_manager->IsKeyPressed(GLFW_KEY_A)
    };

    if (length(input_direction) > 0.01f)
    {
        glm::vec3 direction = normalize(input_direction);
        
        glm::vec3 delta = root_parent->GetPosition() += (direction.x * root_parent->Forward() +
                                                         direction.y * root_parent->Up() +
                                                         direction.z * root_parent->Right()) * m_speed * delta_time;
        
        root_parent->SetPosition(delta);
    }
}
