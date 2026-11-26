#include "NinthCircleEngineContext.h"

#include "AssetManager.h"
#include "Camera.h"
#include "InputManager.h"
#include "Mesh.h"
#include "PlayerController.h"


bool NinthCircleEngineContext::InitializeGLFW()
{
    if (!glfwInit())
    {
        std::cout << "ERROR: Failed to initialize GLFW" << '\n';
        return false;
    }
    
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Ninth Circle Engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    return true;
}

bool NinthCircleEngineContext::InitializeGLAD()
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

bool NinthCircleEngineContext::InitializeEngine()
{
    // Get the working directory path
    m_root_path =  std::filesystem::current_path().string();
    std::ranges::replace(m_root_path, '\\', '/');
    
    // TODO: Remove this when scene loading has been implemented
    Camera* camera = new Camera();
    
    SetRoot(camera);
    
    PlayerController* pc = new PlayerController();
    pc->SetParent(camera);
    
    AssetManager* asset_manager = AssetManager::GetInstance();
    
    asset_manager->LoadShader(m_root_path + "/assets/shaders/simpleShader.vert.glsl", m_root_path + "/assets/shaders/simpleShader.frag.glsl");
    
    Mesh* mesh = new Mesh({}, asset_manager->LoadStaticMeshes(m_root_path + "/assets/static_meshes/soule.obj"), AssetManager::GetInstance()->GetAllShaders().at(m_root_path + "/assets/shaders/simpleShader.vert.glsl" + m_root_path + "/assets/shaders/simpleShader.frag.glsl"));
    mesh->SetParent(camera);
    
    for (auto& static_mesh : mesh->m_static_meshes)
    {
        // TODO: Make this the default texture for any static_mesh without one (nullptr)
        static_mesh->m_texture = asset_manager->LoadTexture(m_root_path + "/assets/textures/missing_texture.png");
    }
    
    mesh->m_static_meshes[0]->m_texture = asset_manager->LoadTexture(m_root_path + "/assets/textures/soule/Dress.png");
    mesh->m_static_meshes[1]->m_texture = asset_manager->LoadTexture(m_root_path + "/assets/textures/white.png");
    mesh->m_static_meshes[2]->m_texture = asset_manager->LoadTexture(m_root_path + "/assets/textures/soule/Eyes.png");
    mesh->m_static_meshes[3]->m_texture = asset_manager->LoadTexture(m_root_path + "/assets/textures/soule/Tail.png");
    mesh->m_static_meshes[4]->m_texture = asset_manager->LoadTexture(m_root_path + "/assets/textures/soule/Pumps.png");
    mesh->m_static_meshes[5]->m_texture = asset_manager->LoadTexture(m_root_path + "/assets/textures/soule/Horns.png");
    mesh->m_static_meshes[6]->m_texture = asset_manager->LoadTexture(m_root_path + "/assets/textures/soule/Hair.png");
    mesh->m_static_meshes[7]->m_texture = asset_manager->LoadTexture(m_root_path + "/assets/textures/soule/Body.png");
    mesh->m_static_meshes[8]->m_texture = asset_manager->LoadTexture(m_root_path + "/assets/textures/black.png");
    
    return true;
}

void NinthCircleEngineContext::Update()
{
    while (m_is_running)
    {
        Logic();
        Render();
    }
}

void NinthCircleEngineContext::Logic()
{
    InputManager::GetInstance()->Update();
    
    // Time
    const float current_frame = static_cast<float>(glfwGetTime());
    m_delta_time = current_frame - m_last_frame;
    m_last_frame = current_frame;
    m_engine_time_milliseconds += m_delta_time;
    
    // Update window size
    int window_width;
    int window_height;
    glfwGetWindowSize(glfwGetCurrentContext(), &window_width, &window_height);

    // Check if we should close the engine
    if (InputManager::GetInstance()->IsKeyJustPressed(GLFW_KEY_F10)) { Exit(); }
    if (glfwWindowShouldClose(glfwGetCurrentContext()))              { Exit(); }
    
    // TODO: Create a 'Viewport' class to handle this instead
    if (InputManager::GetInstance()->IsKeyJustPressed(GLFW_KEY_F))
        InputManager::GetInstance()->IsFocused(!InputManager::GetInstance()->IsFocused());
    
    // Update objects
    if (GetRoot())
        GetRoot()->Update(DeltaTime());
}

void NinthCircleEngineContext::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.17f, 0.34f, 1.0f);

    
    // TODO: Make object render use depth first to begin with the deepest child and then work backwards
    if (Object* root = GetRoot())
    {
        if (Camera* camera = root->GetFirstOfType<Camera>())
        {
            for (auto& [path, shader] : AssetManager::GetInstance()->GetAllShaders())
            {
                shader->SetMatrix4("projection", camera->GetProjection());
                shader->SetMatrix4("view", camera->GetView());
            }
            
            if (GetRoot())
                GetRoot()->Draw();
        }
    }
    
    glfwSwapBuffers(glfwGetCurrentContext());
}

void NinthCircleEngineContext::Start()
{
    if (!InitializeGLFW())   { Exit(); }
    if (!InitializeGLAD())   { Exit(); }
    if (!InitializeEngine()) { Exit(); }
    
    Update();
}

void NinthCircleEngineContext::Exit()
{
    m_is_running = false;
}

bool NinthCircleEngineContext::LoadScene(std::string path)
{
    // TODO: This will import a custom file format to populate the scene
    
    return true;
}
