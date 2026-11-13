#include "StaticMeshLoader.h"

#include <fstream>
#include <sstream>

StaticMesh* StaticMeshLoader::LoadMesh(const std::string& path)
{
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec2> temp_uvs;
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    std::string name;
    
    
    // Load file
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cout << "Failed to open file: " << path << "\n";
        return nullptr;
    }
    
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v")
        {
            glm::vec3 pos;
            ss >> pos.x >> pos.y >> pos.z;
            temp_positions.emplace_back(pos);
        }
        else if (prefix == "vn")
        {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            temp_normals.emplace_back(normal);
        }
        else if (prefix == "vt") {
            glm::vec3 uv;
            ss >> uv.x >> uv.y;
            temp_uvs.emplace_back(uv);
        }
        else if (prefix == "f")
        {
            std::vector<std::string> faceTokens;
            std::string token;
            while (ss >> token)
            {
                faceTokens.push_back(token);
            }
            
            if (faceTokens.size() < 3) continue;

            for (unsigned int i = 0; i < faceTokens.size() - 1; ++i)
            {
                unsigned int triangle_indices[3] = {0, i, i + 1};

                for (int k = 0; k < 3; ++k)
                {
                    std::string s = faceTokens[triangle_indices[k]];
                    unsigned int first_slash  = s.find('/');
                    unsigned int second_slash = s.find('/', first_slash + 1);
                    
                    unsigned int p_idx = std::stoi(s.substr(0, first_slash)) - 1;
                    unsigned int n_idx = std::stoi(s.substr(second_slash + 1)) - 1;
                    unsigned int uv_idx = std::stoi(s.substr(first_slash + 1, second_slash - first_slash - 1)) - 1;
                    
                    Vertex vertex = {
                        temp_positions[p_idx],
                        temp_normals[n_idx],
                        temp_uvs[uv_idx]
                    };
                    
                    // dupe check
                    // int existing_index = -1;
                    // for (unsigned int j = 0; j < vertices.size(); ++j)
                    // {
                    //     if (vertices[j].position == vertex.position &&
                    //         vertices[j].normal == vertex.normal &&
                    //         vertices[j].uv == vertex.uv)
                    //     {
                    //         existing_index = j;
                    //         break;
                    //     }
                    // }
                    //
                    // if (existing_index != -1)
                    // {
                    //     indices.push_back(existing_index);
                    // }
                    // else
                    // {
                        indices.push_back(vertices.size());
                        vertices.push_back(vertex);
                    // }
                }
            }
            
        }
        else if (prefix == "o")
        {
            ss >> name;
        }
    }
    
    
    // Construct mesh
    StaticMesh* mesh = new StaticMesh();
    mesh->m_name = name;
    mesh->InitializeMesh(vertices, indices);
    
    return mesh;
}
