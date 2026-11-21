#pragma once
#include <map>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class InputManager
{
private:
     GLFWwindow* m_window = nullptr;
     glm::dvec2 m_mouse_position;
     glm::dvec2 m_mouse_delta = {0, 0};
     
     bool m_is_focused = false;
     
     // Keeps track of all the key events that have been pressed
     // 0 = released, 1 = pressed, 2 = held since last update
     std::map<int, int> m_key_states;
     
public:
     InputManager(GLFWwindow* window, int width, int height);
     
     void Update();
     void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
     
     bool IsFocused() const { return m_is_focused; }
     void IsFocused(bool value);
     
     bool IsKeyPressed(int key)     const { return m_key_states.contains(key) && m_key_states.at(key) > 0; }
     bool IsKeyJustPressed(int key) const { return m_key_states.contains(key) && m_key_states.at(key) == 1; }
     
     
     glm::dvec2 GetMousePosition() const { return m_mouse_position; }
     glm::dvec2 GetMouseDelta()    const { return m_mouse_delta; }
     
     
};
