#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "assets/shapes/Cube.h"
#include "assets/shapes/Pyramid.h"

#include "Shader.h"
#include "Debugging.h"
#include "assets/shapes/Sphere.h"

const float triangleBuffer[] = {-1, 1, 0,
                                -1, -1, 0,
                                 1, -1, 0};


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
    
    Shader* simpleShader = new Shader;
    
    simpleShader->Initialize("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.vert.glsl", "C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.frag.glsl");
    
    simpleShader->Use();

    const int grid_x = 8;
    const int grid_z = 8;
    
    std::vector<Cube*> cubes;
    std::vector<Pyramid*> pyramids;
    std::vector<Sphere*> spheres;
    
    for (int x = 0; x < grid_x; ++x)
    for (int z = 0; z < grid_z; ++z)
    {
        Cube* cube = new Cube;
        
        cube->m_transform.m_position = {x - grid_x / 2, 0, z - grid_z / 2};
        cube->m_transform.m_scale = {0.2f, 0.2f, 0.2f};
        
        cubes.emplace_back(cube);
        
        
        Pyramid* pyramid = new Pyramid;
        
        pyramid->m_transform.m_position = {x - grid_x / 2, 1, z - grid_z / 2};
        pyramid->m_transform.m_scale = {0.2f, 0.2f, 0.2f};
        
        pyramids.emplace_back(pyramid);
        
        
        Sphere* sphere = new Sphere;
        sphere->m_transform.m_position = {x - grid_x / 2, 2, z - grid_z / 2};
        sphere->m_transform.m_scale = {0.2f, 0.2f, 0.2f};
        
        spheres.emplace_back(sphere);
    }
    
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.17f, 0.34f, 1.0f);
        
        // Draw all our cubes
        simpleShader->SetVec3("aColor", {0.467f, 0.545f, 0.922f});
        for (Cube* cube : cubes)
        {
            cube->m_transform.m_rotation.y = (cosf(glfwGetTime() + cube->m_transform.m_position.x / 5.0f) + 1 / 2) * 360;
            cube->Draw(simpleShader);
        }
        
        // Draw all our pyramids
        simpleShader->SetVec3("aColor", {0.973, 0.647, 0.761});
        for (Pyramid* pyramid : pyramids)
        {
            pyramid->m_transform.m_scale = {(sinf(glfwGetTime() + pyramid->m_transform.m_position.x / 5.0f) + 1 / 2) * 0.2, 0.2, 0.2};
            pyramid->Draw(simpleShader);
        }
        
        // Draw all our spheres
        const float sphere_offset_y = 3;
        simpleShader->SetVec3("aColor", {0.416, 0.69, 0.298});
        for (Sphere* sphere : spheres)
        {
            sphere->m_transform.m_position = {sphere->m_transform.m_position.x, (sinf(glfwGetTime() * 2 + sphere->m_transform.m_position.x)) / 2 + sphere_offset_y ,sphere->m_transform.m_position.z};
            sphere->Draw(simpleShader);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}