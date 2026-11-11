#include <iostream>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Shader.h"
#include "Debugging.h"
#include "Mesh.h"

#include "OBJ-Loader/OBJ_Loader.h"

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
    
    // SHADERS
    Shader* simpleShader = new Shader;
    simpleShader->Initialize("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.vert.glsl", "C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.frag.glsl");
    simpleShader->Use();
    
    
    // MATRIX STUFF
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 10.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    // glm::mat4 projection = glm::ortho(-6.0f, 6.0f, -6.0f, 6.0f, 0.1f, 100.0f);
    
    simpleShader->SetMatrix4("view", view);
    simpleShader->SetMatrix4("projection", projection);

    
    // MESHES
    std::map<std::string, StaticMesh*> staticMeshes;
    
    
    // OBJ_Loader by Bly7: https://github.com/Bly7/OBJ-Loader/
    objl::Loader loader;
    
    loader.LoadFile("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/static_meshes/monkey.obj");
    loader.LoadedMeshes[0].Vertices;
    
    StaticMesh* sm = new StaticMesh;
    sm->InitializeMesh(
        reinterpret_cast<std::vector<Vertex>&>(loader.LoadedMeshes[0].Vertices),
        reinterpret_cast<std::vector<int>&>(loader.LoadedMeshes[0].Indices));
    
    staticMeshes.try_emplace(loader.LoadedMeshes[0].MeshName, sm);
    
    Mesh test_mesh = {
        {},
        staticMeshes.at(loader.LoadedMeshes[0].MeshName),
        simpleShader
    };
    
    
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.17f, 0.34f, 1.0f);
        
        
        test_mesh.m_transform.m_position = {sinf(glfwGetTime() * 2.0f) * 4, cosf(glfwGetTime() * 2.0f) * 4, 0};
        test_mesh.Draw();
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}