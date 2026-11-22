#pragma once
#include <vector>

#include "Transform.h"

class Object
{
    Transform m_transform = Transform::zero();
    
    Object* m_parent = nullptr;
    std::vector<Object*> m_children;
    
public:
    Transform GetTransform() const;
    Transform GetLocalTransform() const { return m_transform; }
    void SetTransform(const Transform& transform) { m_transform = transform; }
    
    glm::vec3 GetPosition() const;
    glm::vec3 GetLocalPosition() const { return m_transform.m_position; }
    void SetPosition(const glm::vec3 position) { m_transform.m_position = position; }
    
    glm::vec3 GetRotation() const;
    glm::vec3 GetLocalRotation() const { return m_transform.m_rotation; }
    void SetRotation(const glm::vec3 rotation) { m_transform.m_rotation = rotation; }
    
    glm::vec3 GetScale() const;
    glm::vec3 GetLocalScale() const { return m_transform.m_scale; }
    void SetScale(const glm::vec3 scale) { m_transform.m_scale = scale; }
    
    
    Object* GetParent() const { return m_parent; }
    Object* GetRootParent(); 
    void SetParent(Object* object);
    
    std::vector<Object*> GetAllChildren() { return m_children; }
    void AddChild(Object* object);
    void RemoveChild(const Object* object);
};
