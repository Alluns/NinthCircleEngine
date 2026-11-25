#pragma once
#include <map>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class InputManager
{
private:
     static inline InputManager* m_singleton;
     
     
     glm::dvec2 m_mouse_position;
     glm::dvec2 m_mouse_delta = {0, 0};
     
     bool m_is_focused = false;
     
     // 0 = released, 1 = pressed, 2 = held since last update
     std::map<int, int> m_key_states;
     
private:
     InputManager();
     
public:
     InputManager(InputManager &other) = delete;
     void operator=(const InputManager&) = delete;
     static InputManager* GetInstance() { return !m_singleton ? m_singleton = new InputManager : m_singleton; }
     
     void Update();
     static void StaticKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
     void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
     
     bool IsFocused() const { return m_is_focused; }
     void IsFocused(bool value);
     
     bool IsKeyPressed(int key)     const { return m_key_states.contains(key) && m_key_states.at(key) > 0; }
     bool IsKeyJustPressed(int key) const { return m_key_states.contains(key) && m_key_states.at(key) == 1; }
     
     
     glm::dvec2 GetMousePosition() const { return m_mouse_position; }
     glm::dvec2 GetMouseDelta()    const { return m_mouse_delta; }
};
