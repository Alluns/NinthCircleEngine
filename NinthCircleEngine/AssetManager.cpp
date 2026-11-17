#include "AssetManager.h"

#include "StaticMeshLoader.h"

AssetManager::~AssetManager()
{
    for (const std::pair<const std::string, StaticMesh*>& static_mesh : m_static_meshes) { delete static_mesh.second; }
    m_static_meshes.clear();
}

std::vector<StaticMesh*> AssetManager::LoadStaticMeshes(const std::string& path)
{
    // If it already exists
    if (m_static_meshes.contains(path))
    {
        std::vector<StaticMesh*> static_meshes;

        for (std::pair<std::string, StaticMesh*> static_mesh : m_static_meshes)
        {
            if (static_mesh.first.starts_with(path)) { static_meshes.emplace_back(static_mesh.second); }
        }
        
        return static_meshes;
    }
    
    // Otherwise load it from the path
    std::vector<StaticMesh*> static_meshes = StaticMeshLoader::LoadMeshFile(path);

    for (StaticMesh* static_mesh : static_meshes)
        m_static_meshes.insert({path + "/" + static_mesh->m_name, static_mesh});
    
    return static_meshes;
}

Texture* AssetManager::LoadTexture(const std::string& path)
{
    if (m_textures.contains(path)) { return m_textures[path]; }
    
    Texture* texture = new Texture(path);
    m_textures.insert({path, texture});
    
    return texture;
}
