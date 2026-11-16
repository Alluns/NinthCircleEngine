#include "AssetManager.h"

#include "StaticMeshLoader.h"

AssetManager::~AssetManager()
{
    for (const std::pair<const std::string, StaticMesh*>& static_mesh : m_static_meshes) { delete static_mesh.second; }
    m_static_meshes.clear();
}

StaticMesh* AssetManager::LoadStaticMesh(const std::string& path)
{
    if (m_static_meshes.contains(path))
    {
        return m_static_meshes[path];
    }
    
    StaticMesh* static_mesh = StaticMeshLoader::LoadMesh(path);
    m_static_meshes.insert({path, static_mesh});
    
    return static_mesh;
}
