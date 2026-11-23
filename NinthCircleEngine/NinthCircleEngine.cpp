#include <iostream>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

#include "AssetManager.h"
#include "Camera.h"
#include "InputManager.h"
#include "Shader.h"
#include "Mesh.h"
#include "PlayerController.h"


float g_delta_time = 0.0f;
float g_last_frame = 0.0f;

InputManager* g_input_manager;
std::vector<Object*> g_objects;

const int g_window_width = 1080;
const int g_window_height = 720;

Shader* g_simpleShader;


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
    Camera* camera = new Camera(g_input_manager, g_window_width, g_window_height);
    g_objects.emplace_back(camera);
    
    // Player Controller
    PlayerController* player_controller = new PlayerController(g_input_manager);
    player_controller->SetParent(camera);
    g_objects.emplace_back(player_controller);
    
    // SHADERS
    g_simpleShader = new Shader;
    g_simpleShader->Initialize("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.vert.glsl", "C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.frag.glsl");
    g_simpleShader->Use();
    
    // MESHES
    AssetManager* asset_manager = new AssetManager;

    Mesh* mesh = new Mesh({}, asset_manager->LoadStaticMeshes("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/static_meshes/soule.obj"), g_simpleShader);

    for (auto& static_mesh : mesh->m_static_meshes)
    {
        // TODO: Make this the default texture for any static_mesh without one (nullptr)
        static_mesh->m_texture = asset_manager->LoadTexture("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/missing_texture.png");
    }
    
    mesh->m_static_meshes[0]->m_texture = asset_manager->LoadTexture("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Dress.png");
    mesh->m_static_meshes[1]->m_texture = asset_manager->LoadTexture("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/white.png");
    mesh->m_static_meshes[2]->m_texture = asset_manager->LoadTexture("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Eyes.png");
    mesh->m_static_meshes[3]->m_texture = asset_manager->LoadTexture("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Tail.png");
    mesh->m_static_meshes[4]->m_texture = asset_manager->LoadTexture("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Pumps.png");
    mesh->m_static_meshes[5]->m_texture = asset_manager->LoadTexture("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Horns.png");
    mesh->m_static_meshes[6]->m_texture = asset_manager->LoadTexture("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Hair.png");
    mesh->m_static_meshes[7]->m_texture = asset_manager->LoadTexture("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/soule/Body.png");
    mesh->m_static_meshes[8]->m_texture = asset_manager->LoadTexture("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/textures/black.png");
    
    g_objects.emplace_back(mesh);
    
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
    
    GLFWwindow* window = glfwCreateWindow(g_window_width, g_window_height, "Ninth Circle Engine", nullptr, nullptr);
    
    g_input_manager = new InputManager(window, g_window_width, g_window_height);
    
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
    // glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    
    return true;
}

void Logic()
{
    // Calculate delta time
    const float current_frame = static_cast<float>(glfwGetTime());
    g_delta_time = current_frame - g_last_frame;
    g_last_frame = current_frame;
    
    // Input Manager
    if (g_input_manager->IsKeyJustPressed(GLFW_KEY_F))
        g_input_manager->IsFocused(!g_input_manager->IsFocused());
    
    // Create and remove cameras
    if (g_input_manager->IsKeyJustPressed(GLFW_KEY_KP_ADD))
    {
        Camera* camera = new Camera(g_input_manager, g_window_width, g_window_height);
        g_objects.emplace_back(camera);
    }
    
    // Objects
    for (const auto& object : g_objects)
        object->Update(g_delta_time);
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.17f, 0.34f, 1.0f);
    
    std::vector<Camera*> cameras;
    
    for (Object* const& object : g_objects)
        if (Camera* camera = dynamic_cast<Camera*>(object))
            cameras.emplace_back(camera);

    if (!cameras.empty())
    {
        int columns = static_cast<int>(floor(sqrt(cameras.size() - 1))) + 1;
        int rows = static_cast<int>(ceil(static_cast<double>(cameras.size()) / static_cast<double>(columns)));
        
        int window_width;
        int window_height;
        glfwGetWindowSize(glfwGetCurrentContext(), &window_width, &window_height);
        
        int viewport_width = window_width / columns;
        int viewport_height = window_height / rows;
        
        for (int i = 0; i < cameras.size(); ++i)
        {
            int x = i % columns;
            int y = (i - x) / rows;
            
            glViewport(x * viewport_width, y * viewport_height, viewport_width, viewport_height);
            cameras[i]->SetResolution(viewport_width, viewport_height);
        
            g_simpleShader->SetMatrix4("projection", cameras[i]->GetProjection());
            g_simpleShader->SetMatrix4("view", cameras[i]->GetView());
    
            for (const auto& object : g_objects)
                object->Draw();
        }
    }
    
    glfwSwapBuffers(glfwGetCurrentContext());
}