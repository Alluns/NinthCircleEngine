#pragma once
#include "InputManager.h"
#include "Object.h"

class PlayerController : public Object
{
protected:
    InputManager* m_input_manager = nullptr;
    
    float m_speed = 8.0f;
    float m_mouse_sensitivity = 0.1f;
    
    float pitch = 0.0f;
    float yaw = -90.0f;
    
public:
    PlayerController(InputManager* input_manager);
    
    void update(const float delta_time);
};
