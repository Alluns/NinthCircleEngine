#pragma once

#include <map>
#include <string>
#include <vector>

#include "StaticMesh.h"

class AssetManager
{
    static inline AssetManager* m_singleton;
    
    std::map<std::string, StaticMesh*> m_static_meshes;
    std::map<std::string, Texture*>    m_textures;
    std::map<std::string, Shader*>     m_shaders;
    
private:
    AssetManager() = default;
    
public:
    ~AssetManager();
    
    AssetManager(AssetManager &other) = delete;
    void operator=(const AssetManager&) = delete;
    static AssetManager* GetInstance() { return !m_singleton ? m_singleton = new AssetManager : m_singleton; }
    
    std::vector<StaticMesh*> LoadStaticMeshes(const std::string& path);
    Texture* LoadTexture(const std::string& path);
    
    std::map<std::string, StaticMesh*> GetAllStaticMeshes() { return m_static_meshes; }
    std::map<std::string, Texture*> GetAllTextures()        { return m_textures; }
    
    std::map<std::string, Shader*> GetAllShaders() { return m_shaders; }
    Shader* LoadShader(const std::string& vertex_path, const std::string& fragment_path);
};
