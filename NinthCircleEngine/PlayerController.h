#pragma once
#include "Object.h"

class PlayerController : public Object
{
protected:
    float m_speed = 8.0f;
    float m_mouse_sensitivity = 0.1f;
    
    float pitch = 0.0f;
    float yaw = -90.0f;
    
public:
    PlayerController() = default;
    PlayerController(Object* parent_object);
    
    void Update(float delta_time) override;
};
