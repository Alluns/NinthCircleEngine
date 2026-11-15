#pragma once
#include <map>
#include <string>

#include "Mesh.h"
#include "StaticMesh.h"

class AssetManager
{
private:
    // TODO: Add support for shaders
    std::map<std::string, StaticMesh*> m_static_meshes;
    // TODO: Add support for textures
    
public:
    ~AssetManager();
    
    // TODO: Add support for shaders
    StaticMesh* LoadStaticMesh(const std::string& path);
    // TODO: Add support for textures
    
    std::map<std::string, StaticMesh*> GetAllStaticMeshes() { return m_static_meshes; }
};
