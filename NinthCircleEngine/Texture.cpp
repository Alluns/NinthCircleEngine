#include "Texture.h"

#include <iostream>

#include "glad/glad.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path)
{
    glGenTextures(1, &m_texture_object);
    Load(path);
}

void Texture::Load(const std::string& path)
{
    stbi_set_flip_vertically_on_load(true);
    
    unsigned char *data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 4);
    
    if (!data)
    {
        std::cout << "Failed to load texture from path (" << path << ")\n";
        return;
    }
    
    glBindTexture(GL_TEXTURE_2D, m_texture_object);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Use()
{
    glBindTexture(GL_TEXTURE_2D, m_texture_object);
}
