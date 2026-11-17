#pragma once

#include <vector>
#include <string>

#include "StaticMesh.h"

class StaticMeshLoader
{
public:    
    static std::vector<StaticMesh*> LoadMeshFile(const std::string& path);
};
