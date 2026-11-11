#pragma once
#include "StaticMesh.h"

class StaticMeshLoader
{
public:
    static StaticMesh* LoadMesh(const std::string& path);
};
