#pragma once

#include "Mesh.h"
#include "Object.h"
#include "Shader.h"

class NinthCircleEngineContext
{
    static inline NinthCircleEngineContext* m_singleton;
    
    bool m_is_running = true;
    float m_delta_time = 0.0f;
    float m_last_frame = 0.0f;
    double m_engine_time_milliseconds = 0.0f; 
    
    Object* m_root = nullptr;
    
    Shader* shader;
    Mesh* mesh;
    
private:
    NinthCircleEngineContext() = default;
    
    // bool LoadConfig();
    bool InitializeGLFW();
    bool InitializeGLAD();
    bool InitializeEngine();
    
    void Update();
    void Logic();
    void Render();
    
public:
    NinthCircleEngineContext(NinthCircleEngineContext &other) = delete;
    void operator=(const NinthCircleEngineContext&) = delete;
    static NinthCircleEngineContext* Engine() { return !m_singleton ? m_singleton = new NinthCircleEngineContext : m_singleton; }
    
    void Start();
    void Exit();
    
    bool LoadScene(std::string path);
    
    /**
     * @return The scene's root object, or 'nullptr' if the scene doesn't have any objects.
     */
    Object* GetRoot() const { return m_root; }
    
    void SetRoot(Object* object) { m_root = object; }
    
    float DeltaTime() const { return m_delta_time; }
    double GetTime() const { return m_engine_time_milliseconds; }
    int GetTimeSeconds() const { return static_cast<int>(floor(m_engine_time_milliseconds / 1000)); }
};
