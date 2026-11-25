#include "InputManager.h"

#include <ranges>

InputManager::InputManager()
{
    GLFWwindow* window = glfwGetCurrentContext();
    
    int window_width;
    int window_height;
    glfwGetWindowSize(window, &window_width, &window_height);
    
    m_mouse_position = {static_cast<float>(window_width) / 2.0f, static_cast<float>(window_height) / 2.0f};
    
    glfwSetKeyCallback(window, StaticKeyCallback);
}

void InputManager::Update()
{
    for (int& state : m_key_states | std::views::values)
        if (state == 1) { state = 2; }
    
    glfwPollEvents();
    
    // MOUSE
    glm::dvec2 last_mouse_position = m_mouse_position;
    
    glfwGetCursorPos(glfwGetCurrentContext(), &m_mouse_position.x, &m_mouse_position.y);
    m_mouse_delta = m_mouse_position - last_mouse_position;
}

void InputManager::StaticKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    GetInstance()->KeyCallback(window, key, scancode, action, mods);
}

void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (!m_key_states.contains(key)) m_key_states[key] = 0;
    
         if (action == GLFW_PRESS && m_key_states[key] == 0) { m_key_states[key] = 1; }
    else if (action == GLFW_RELEASE)                         { m_key_states[key] = 0; }
}

void InputManager::IsFocused(bool value)
{
    m_is_focused = value;
    
    if (m_is_focused)
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
