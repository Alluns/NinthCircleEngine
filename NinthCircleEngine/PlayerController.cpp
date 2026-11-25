#include "PlayerController.h"

#include <algorithm>
#include <glm/trigonometric.hpp>

#include "InputManager.h"

PlayerController::PlayerController(Object* parent_object)
{
    this->SetParent(parent_object);
}

void PlayerController::Update(const float delta_time)
{
    Object::Update(delta_time);
    
    if (!InputManager::GetInstance()->IsFocused()) { return; }
    
    Object* root_parent = GetRootParent();
    
    
    // ROTATION
    glm::dvec2 delta = InputManager::GetInstance()->GetMouseDelta();
    
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
        InputManager::GetInstance()->IsKeyPressed(GLFW_KEY_W) - InputManager::GetInstance()->IsKeyPressed(GLFW_KEY_S),
        InputManager::GetInstance()->IsKeyPressed(GLFW_KEY_SPACE) - InputManager::GetInstance()->IsKeyPressed(GLFW_KEY_LEFT_CONTROL),
        InputManager::GetInstance()->IsKeyPressed(GLFW_KEY_D) - InputManager::GetInstance()->IsKeyPressed(GLFW_KEY_A)
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
