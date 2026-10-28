#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "Transform.h"

void drawTriangle(Transform transform, glm::vec3 color);
void drawRectangle(Transform transform, glm::vec3 color);

const float triangleBuffer[] = {-1, 1, 0,
                                -1, -1, 0,
                                 1, -1, 0};

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform vec3 aOffset;\n"
    "uniform vec3 aRotation;\n"
    "uniform vec3 aScale;\n"
    "uniform vec3 aColor;\n"
    "out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   vec3 scalePos = aPos * aScale;\n"
    "   vec3 rotPos = vec3(scalePos.x * cos(aRotation.x) - scalePos.y * sin(aRotation.x), scalePos.y * cos(aRotation.x) + scalePos.x * sin(aRotation.x), 1.0f);\n"
    "   gl_Position = vec4(rotPos + aOffset, 1.0);\n"
    "   vertexColor = vec4(aColor, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "in vec4 vertexColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vertexColor;\n"
    "}\0";

unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;
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
    
    // PREPARE SHADER STUFF
    //   VERTEX SHADER
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    int result;
    char Log[512];
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, Log);
        std::cout << "Failed to compile vertex shader \n" << Log << '\n';
    }
    
    //   FRAGMENT SHADER
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    //   SHADER PROGRAM
    shaderProgram = glCreateProgram();
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    glLinkProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //   VBO AND STUFF
    glGenBuffers(1, &VBO);
    
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleBuffer), triangleBuffer, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // FINISHED PREPARING SHADER STUFF
    
    
    aColorLocation = glGetUniformLocation(shaderProgram, "aColor");
    aOffsetLocation = glGetUniformLocation(shaderProgram, "aOffset");
    aRotationLocation = glGetUniformLocation(shaderProgram, "aRotation");
    aScaleLocation = glGetUniformLocation(shaderProgram, "aScale");
    
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0.1f, 0.17f, 0.34f, 1.0f);
        
        // Grass
        drawRectangle({{0, -1, 0}, {0, 0, 0}, {2, 0.5, 1}}, {0.043, 0.91, 0.506});
        
        // Wall
        drawRectangle({{0, -0.25, 0}, {0, 0, 0}, {0.5, 0.25, 1}}, {1, 0.247, 0.204});
        
        // Roof
        drawTriangle({{0.25, 0.25, 0}, {0, 0, 0}, {0.25, 0.25, 1}}, {0.118, 0.153, 0.18});
        drawTriangle({{-0.25, 0.25, 0}, {glm::pi<float>()/2, 0, 0}, {0.25, 0.25, 1}}, {0.118, 0.153, 0.18});

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
    glUseProgram(shaderProgram);
    
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