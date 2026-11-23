#pragma once
#include <glm/ext/matrix_float4x4.hpp>

#include "InputManager.h"
#include "Object.h"

class Camera: public Object
{
protected:
    bool m_is_orthographic = false;
    
    InputManager* m_input_manager;
    
    int m_width = 0;
    int m_height = 0;
    
public:
    Camera(InputManager* input_manager, int width, int height);
    
    glm::mat4 GetView();
    glm::mat4 GetProjection();
    
    void Update(float delta_time) override;
    
    void SetResolution(int width, int height) { m_width = width; m_height = height; }
    float AspectRatio() const { return static_cast<float>(m_width) / static_cast<float>(m_height); }
    
    void SetIsOrthographic(const bool value) { m_is_orthographic = value; }
    bool IsOrthographic() const { return m_is_orthographic; }
};
