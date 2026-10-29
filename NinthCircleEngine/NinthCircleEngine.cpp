#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Transform.h"

void drawTriangle(Transform transform, glm::vec3 color);
void drawRectangle(Transform transform, glm::vec3 color);

const float triangleBuffer[] = {-1, 1, 0,
                                -1, -1, 0,
                                 1, -1, 0};

unsigned int VBO;
unsigned int VAO;

int aColorLocation;
int aOffsetLocation;
int aRotationLocation;
int aScaleLocation;

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
    
    //Prepare shader stuff
    glGenBuffers(1, &VBO);
    
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleBuffer), triangleBuffer, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    Shader* simpleShader = new Shader;
    
    simpleShader->Initialize("C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.vert.glsl", "C:/Users/allan.backman/Documents/NinthCircleEngine/NinthCircleEngine/assets/shaders/simpleShader.frag.glsl");
    
    simpleShader->Use();
    
    aColorLocation = glGetUniformLocation(simpleShader->aShaderProgram, "aColor");
    aOffsetLocation = glGetUniformLocation(simpleShader->aShaderProgram, "aOffset");
    aRotationLocation = glGetUniformLocation(simpleShader->aShaderProgram, "aRotation");
    aScaleLocation = glGetUniformLocation(simpleShader->aShaderProgram, "aScale");
    // FINISHED PREPARING SHADER STUFF
    
    // glGetErrors
    while (true)
    {
        auto error = glGetError();
        
        if (error)
            std::cout << "glGetError: " << error <<'\n';
        else
            break;
    }
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f, 0.17f, 0.34f, 1.0f);
        
        int state = glfwGetKey(window, GLFW_KEY_SPACE);
        glm::vec3 roofColor = (state == GLFW_PRESS) ? glm::vec3(0.443, 0.345, 0.886) : glm::vec3(0.118, 0.153, 0.18);
        
        // Grass
        drawRectangle({{0, -1, 0}, {0, 0, 0}, {2, 0.5, 1}}, {0.043, 0.91, 0.506});
        
        // Wall
        drawRectangle({{0, -0.25, 0}, {0, 0, 0}, {0.5, 0.25, 1}}, {1, 0.247, 0.204});
        
        // Roof
        drawTriangle({{0.25, 0.25, 0}, {0, 0, 0}, {0.25, 0.25, 1}}, roofColor);
        drawTriangle({{-0.25, 0.25, 0}, {glm::pi<float>()/2, 0, 0}, {0.25, 0.25, 1}}, roofColor);

        // Windows
        drawRectangle({{-0.25, -0.1875, 0}, {glm::pi<float>()/4, 0, 0}, {0.0625f, 0.0625f, 1}}, {0.294, 0.812, 0.98});
        drawRectangle({{-0.25, -0.1875, 0}, {0, 0, 0}, {0.0625f, 0.0625f, 1}}, {0.294, 0.812, 0.98});
        drawRectangle({{0.25, -0.1875, 0}, {0, 0, 0}, {0.0625f, 0.125f, 1}}, {0.294, 0.812, 0.98});
        
        // Door
        drawRectangle({{0, -0.375, 0}, {0, 0, 0}, {0.0625f, 0.125f, 1}}, {0.118, 0.153, 0.18});
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}

void drawTriangle(Transform transform, glm::vec3 color)
{    
    glUniform3fv(aColorLocation, 1, glm::value_ptr(color));
    glUniform3fv(aOffsetLocation, 1, glm::value_ptr(transform.aPosition));
    glUniform3fv(aRotationLocation, 1, glm::value_ptr(transform.aRotation));
    glUniform3fv(aScaleLocation, 1, glm::value_ptr(transform.aScale));
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void drawRectangle(Transform transform, glm::vec3 color)
{
    Transform triangle1 = transform;
    
    Transform triangle2 = {
        transform.aPosition,
        transform.aRotation + glm::pi<float>(),
        transform.aScale
    };
    
    drawTriangle(triangle1, color);
    drawTriangle(triangle2, color);
}