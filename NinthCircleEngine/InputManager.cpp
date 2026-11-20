#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window, const int width, const int height)
{
    m_window = window;
    m_mouse_position = {static_cast<float>(width) / 2.0f, static_cast<float>(height) / 2.0f};
}

void InputManager::Update()
{
    // MOUSE
    glm::dvec2 last_mouse_position = m_mouse_position;
    
    glfwGetCursorPos(m_window, &m_mouse_position.x, &m_mouse_position.y);
    m_mouse_delta = m_mouse_position - last_mouse_position;
}

bool InputManager::IsKeyPressed(int key)
{
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}

void InputManager::IsFocused(bool value)
{
    m_is_focused = value;
    
    if (m_is_focused)
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
