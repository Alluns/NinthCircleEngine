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
    std::vector<Mesh*> meshes;

    Mesh* mesh = new Mesh({}, asset_manager->LoadStaticMeshes("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/static_meshes/soule.obj"), simpleShader);

    for (auto& static_mesh : mesh->m_static_meshes)
    {
        // TODO: Make this the default texture for any static_mesh without one (nullptr)
        static_mesh->m_texture = asset_manager->LoadTexture("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/missing_texture.png");
    }
    
    mesh->m_static_meshes[0]->m_texture = asset_manager->LoadTexture("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Dress.png");
    mesh->m_static_meshes[2]->m_texture = asset_manager->LoadTexture("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Eyes.png");
    mesh->m_static_meshes[3]->m_texture = asset_manager->LoadTexture("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Tail.png");
    mesh->m_static_meshes[4]->m_texture = asset_manager->LoadTexture("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Pumps.png");
    mesh->m_static_meshes[5]->m_texture = asset_manager->LoadTexture("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Horns.png");
    mesh->m_static_meshes[6]->m_texture = asset_manager->LoadTexture("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Hair.png");
    mesh->m_static_meshes[7]->m_texture = asset_manager->LoadTexture("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Body.png");
    
    meshes.emplace_back(mesh);
    
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