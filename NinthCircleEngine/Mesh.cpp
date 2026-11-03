#include "Mesh.h"

#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Debugging.h"

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<int>& indices)
{
    m_indexCount = indices.size();
    
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    
    m_EBO = 0;
    if (!indices.empty())
    {
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);
    }
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    glCheckError();
    
    m_transform = glm::translate(m_transform, {0, 0, -10});
    m_transform = glm::rotate(m_transform, glm::radians(45.0f), glm::vec3(0.5f, 1.0f, 0));
    m_transform = glm::scale(m_transform, glm::vec3(1.5f, 1.5f, 1.5f));
    
    m_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    m_projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
}

Mesh::~Mesh()
{
    if (m_VBO) glDeleteBuffers(1, &m_VBO);
    if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
}

void Mesh::Draw(Shader* aShader)
{
    aShader->SetMatrix4("transform", m_transform);
    aShader->SetMatrix4("view", m_view);
    aShader->SetMatrix4("projection", m_projection);
    
    aShader->Use();
    
    glBindVertexArray(m_VAO);

    if (m_EBO == 0)
    {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    } else
    {
        glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
    }
    
    glBindVertexArray(0);
}
