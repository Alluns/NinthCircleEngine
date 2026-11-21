#include <iostream>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "AssetManager.h"
#include "Camera.h"
#include "InputManager.h"
#include "Shader.h"
#include "Mesh.h"


float g_delta_time = 0.0f;
float g_last_frame = 0.0f;

InputManager* g_input_manager;
std::vector<Mesh*> g_meshes;
Shader* g_simpleShader;
Camera* g_camera;


bool Initialize();
bool InitializeOpenGL();

void Logic();
void Render();

GLFWwindow* OpenWindow();


int main(int argc, char* argv[])
{
    if (!Initialize()) return -1;
    
    while (!glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        g_input_manager->Update();
        Logic();
        Render();
    }
    
    return 0;
}

bool Initialize()
{
    GLFWwindow* window = OpenWindow();
    glfwMakeContextCurrent(window);

    if (!InitializeOpenGL()) return false;
    
    // CAMERA
    g_camera = new Camera;
    
    // SHADERS
    g_simpleShader = new Shader;
    g_simpleShader->Initialize("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.vert.glsl", "C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.frag.glsl");
    g_simpleShader->Use();
    
    // MATRIX STUFF
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1080.0f/720.0f, 0.1f, 100.0f);
    // glm::mat4 projection = glm::ortho(-6.0f, 6.0f, -6.0f, 6.0f, 0.1f, 100.0f);
    
    g_simpleShader->SetMatrix4("projection", projection);
    g_simpleShader->SetVec3("color", {1.0f, 1.0f, 1.0f});
    
    // MESHES
    AssetManager* asset_manager = new AssetManager;

    Mesh* mesh = new Mesh({}, asset_manager->LoadStaticMeshes("C:/Users/allan/Documents/NinthCircleEngine/NinthCircleEngine/assets/static_meshes/soule.obj"), g_simpleShader);

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
    
    g_meshes.emplace_back(mesh);
    
    return true;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    g_input_manager->KeyCallback(window, key, scancode, action, mods);
}

GLFWwindow* OpenWindow()
{
    if (!glfwInit())
    {
        std::cout << "ERROR: Failed to initialize glfw" << '\n';
        return nullptr;
    }
    
    const int width = 1080;
    const int height = 720;
    
    GLFWwindow* window = glfwCreateWindow(width, height, "Ninth Circle Engine", nullptr, nullptr);
    
    g_input_manager = new InputManager(window, width, height);
    
    glfwSetKeyCallback(window, KeyCallback);
    
    return window;
}

bool InitializeOpenGL()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR: Failed to initialize GLAD" << '\n';
        return false;
    }
    
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    
    return true;
}

void Logic()
{
    // Calculate delta time
    const float current_frame = static_cast<float>(glfwGetTime());
    g_delta_time = current_frame - g_last_frame;
    g_last_frame = current_frame;
    
    // Camera
    if (g_input_manager->IsKeyJustPressed(GLFW_KEY_F))
    {
        g_input_manager->IsFocused(!g_input_manager->IsFocused());
    }

    if (g_input_manager->IsFocused())
    {
        glm::vec3 direction = {
            g_input_manager->IsKeyPressed(GLFW_KEY_W) - g_input_manager->IsKeyPressed(GLFW_KEY_S),
            g_input_manager->IsKeyPressed(GLFW_KEY_SPACE) - g_input_manager->IsKeyPressed(GLFW_KEY_LEFT_CONTROL),
            g_input_manager->IsKeyPressed(GLFW_KEY_D) - g_input_manager->IsKeyPressed(GLFW_KEY_A),
        };
    
        g_camera->Update(g_input_manager->GetMouseDelta(), direction, g_delta_time);
    }
    
    g_simpleShader->SetMatrix4("view", g_camera->GetView());
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.17f, 0.34f, 1.0f);
    
    for (auto& mesh : g_meshes)
        mesh->Draw();
        
    glfwSwapBuffers(glfwGetCurrentContext());
}