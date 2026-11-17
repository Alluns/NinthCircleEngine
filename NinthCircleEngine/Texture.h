#pragma once
#include <string>

class Texture
{
protected:
    unsigned int m_texture_object = 0;
    int m_width = 0;
    int m_height = 0;
    int m_channels = 0;
    
public:
    Texture(const std::string& path);
    
    void Load(const std::string& path);
    void Use();
};
