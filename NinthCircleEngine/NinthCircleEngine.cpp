#include <iostream>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "assets/shapes/Cube.h"
#include "assets/shapes/Sphere.h"
#include "assets/shapes/Pyramid.h"

#include "Shader.h"
#include "Debugging.h"
#include "Mesh.h"


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
    
    staticMeshes.try_emplace("cube",    new Cube());
    staticMeshes.try_emplace("sphere",  new Sphere());
    staticMeshes.try_emplace("pyramid", new Pyramid());
    
    Mesh cube = {
        {},
        staticMeshes.at("cube"),
        simpleShader
    };
    
    
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.17f, 0.34f, 1.0f);
        
        cube.m_transform.m_position = {sinf(glfwGetTime() * 2.0f) * 4, cosf(glfwGetTime()* 2.0f) * 4, 0};
        
        // Draw all our cubes
        simpleShader->SetVec3("aColor", {0.467f, 0.545f, 0.922f});
        cube.Draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}