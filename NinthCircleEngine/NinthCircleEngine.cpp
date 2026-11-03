#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Cube.h"
#include "Shader.h"
#include "Debugging.h"

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
    
    Cube* cube = new Cube;
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f, 0.17f, 0.34f, 1.0f);
        
        cube->Draw(simpleShader);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}