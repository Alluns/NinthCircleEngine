#pragma once
#include <glm/ext/matrix_float4x4.hpp>

#include "Object.h"

class Camera: public Object
{
protected:
    bool m_is_orthographic = false;
    
    int m_width = 0;
    int m_height = 0;
    
public:
    Camera(int width, int height);
    
    glm::mat4 GetView();
    glm::mat4 GetProjection();
    
    float AspectRatio() const { return static_cast<float>(m_width) / static_cast<float>(m_height); }
    
    void SetIsOrthographic(const bool value) { m_is_orthographic = value; }
    bool IsOrthographic() const { return m_is_orthographic; }
};
