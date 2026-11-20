#pragma once
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class InputManager
{
private:
     GLFWwindow* m_window = nullptr;
     glm::dvec2 m_mouse_position;
     glm::dvec2 m_mouse_delta = {0, 0};
     
     bool m_is_focused = false;
     
public:
     InputManager(GLFWwindow* window, int width, int height);
     
     void Update();
     bool IsFocused() const { return m_is_focused; }
     void IsFocused(bool value);
     
     bool IsKeyPressed(int key);
     
     
     glm::dvec2 GetMousePosition() const { return m_mouse_position; }
     glm::dvec2 GetMouseDelta()    const { return m_mouse_delta; }
     
     
};
