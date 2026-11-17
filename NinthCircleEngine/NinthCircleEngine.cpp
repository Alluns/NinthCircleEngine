#include <iostream>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "AssetManager.h"
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"


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
    simpleShader->Initialize("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.vert.glsl", "C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.frag.glsl");
    simpleShader->Use();
    
    // MATRIX STUFF
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    // glm::mat4 projection = glm::ortho(-6.0f, 6.0f, -6.0f, 6.0f, 0.1f, 100.0f);
    
    simpleShader->SetMatrix4("projection", projection);
    simpleShader->SetVec3("color", {1.0f, 1.0f, 1.0f});
    
    // MESHES
    AssetManager* asset_manager = new AssetManager;
    std::vector<StaticMesh*> static_meshes;
    std::vector<Mesh*> meshes;
    
    asset_manager->LoadStaticMesh("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/static_meshes/monkey.obj");
    
    asset_manager->LoadStaticMesh("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/static_meshes/soule.obj");
    
    asset_manager->GetAllStaticMeshes().at("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/static_meshes/soule.obj")->m_texture = asset_manager->LoadTexture("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Dress.png");

    for (std::pair<const std::string, StaticMesh*> static_mesh : asset_manager->GetAllStaticMeshes())
    {
        Mesh* mesh = new Mesh({}, static_mesh.second, simpleShader);
        meshes.emplace_back(mesh);
    }
    
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

        for (int i = 0; i < meshes.size(); ++i)
        {
            meshes[i]->m_transform.m_position = {i * 3, cosf(glfwGetTime() * 0) * 0.1f * -1, 0};
            meshes[i]->Draw();
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}