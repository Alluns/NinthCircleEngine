#include <iostream>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "StaticMeshLoader.h"

#include "OBJ-Loader/OBJ_Loader.h"


float g_delta_time = 0.0f;
float g_last_frame = 0.0f;


int main(int argc, char* argv[])
{
    if (!glfwInit())
    {
        std::cout << "failed to initialize glfw" << '\n';
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(720, 720, "Ninth Circle Engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << '\n';
        return -1;
    }
    
    // CAMERA
    Camera* camera = new Camera;
    
    // SHADERS
    Shader* simpleShader = new Shader;
    simpleShader->Initialize("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.vert.glsl", "C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.frag.glsl");
    simpleShader->Use();
    
    
    // MATRIX STUFF
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    // glm::mat4 projection = glm::ortho(-6.0f, 6.0f, -6.0f, 6.0f, 0.1f, 100.0f);
    
    simpleShader->SetMatrix4("projection", projection);

    
    // MESHES
    std::map<std::string, StaticMesh*> staticMeshes;
    std::vector<Mesh> Meshes;
    
    
    // OBJ_Loader by Bly7: https://github.com/Bly7/OBJ-Loader/
    objl::Loader loader;
    
    loader.LoadFile("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/static_meshes/monkey.obj");
    loader.LoadedMeshes[0].Vertices;

    for (auto loaded_mesh : loader.LoadedMeshes)
    {
        StaticMesh* sm = new StaticMesh;
        sm->InitializeMesh(reinterpret_cast<std::vector<Vertex>&>(loaded_mesh.Vertices), loaded_mesh.Indices);
    
        staticMeshes.try_emplace(loaded_mesh.MeshName, sm);
        
        Mesh mesh = {
            {},
            staticMeshes.at(loaded_mesh.MeshName),
            simpleShader
        };
        
        Meshes.emplace_back(mesh);
    }
    
    // Custom .obj loader
    StaticMesh* sm2 = StaticMeshLoader::LoadMesh("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/static_meshes/monkey.obj");
    Mesh* mesh2 = new Mesh({}, sm2, simpleShader);
    
    
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        float current_frame = glfwGetTime();
        g_delta_time = current_frame - g_last_frame;
        g_last_frame = current_frame;
        
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.17f, 0.34f, 1.0f);

        
        // Camera
        camera->ProcessInput(window, g_delta_time);
        simpleShader->SetMatrix4("view", camera->GetView());
        
        
        for (Mesh& mesh : Meshes)
        {
            mesh.m_transform.m_position = {sinf(glfwGetTime() * 2.0f) * 2, cosf(glfwGetTime() * 2.0f) * 2, 0};
            mesh.Draw();
        }
        
        
        mesh2->m_transform.m_position = {sinf(glfwGetTime() * 2.0f) * 2 * -1, cosf(glfwGetTime() * 2.0f) * 2 * -1, 0};
        mesh2->Draw();
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}