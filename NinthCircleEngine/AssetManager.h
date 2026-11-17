#pragma once

#include <map>
#include <string>
#include <vector>

#include "StaticMesh.h"

class AssetManager
{
private:
    // TODO: Add support for shaders
    std::map<std::string, StaticMesh*> m_static_meshes;
    std::map<std::string, Texture*>    m_textures;
    
public:
    ~AssetManager();
    
    // TODO: Add support for shaders
    std::vector<StaticMesh*> LoadStaticMeshes(const std::string& path);
    Texture* LoadTexture(const std::string& path);
    
    std::map<std::string, StaticMesh*> GetAllStaticMeshes() { return m_static_meshes; }
    std::map<std::string, Texture*> GetAllTextures()        { return m_textures; }
};
