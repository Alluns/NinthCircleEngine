#pragma once
#include <vector>

#include "Transform.h"

class Object
{
    Transform m_transform = Transform::zero();
    
    glm::vec3 m_forward  = {0, 0, -1.0f};
    glm::vec3 m_up       = {0, 1.0f, 0};
    glm::vec3 m_right    = {1.0f, 0, 0};
    
    Object* m_parent = nullptr;
    std::vector<Object*> m_children;
    
public:
    virtual ~Object();
    
    virtual void Update(const float delta_time) {}
    virtual void Draw() {}
    
    glm::vec3 Forward() const { return m_forward; }
    void SetForward(glm::vec3 direction) { m_forward = direction; }
    
    glm::vec3 Up()      const { return m_up; }
    void SetUp(glm::vec3 direction)      { m_up = direction; }
    
    glm::vec3 Right()   const { return m_right; }
    void SetRight(glm::vec3 direction)   { m_right = direction; }
    
    
    Transform GetTransform();
    Transform GetLocalTransform() const { return m_transform; }
    void SetTransform(const Transform& transform) { m_transform = transform; }
    
    glm::vec3 GetPosition();
    glm::vec3 GetLocalPosition() const { return m_transform.m_position; }
    void SetPosition(const glm::vec3 position) { m_transform.m_position = position; }
    
    glm::vec3 GetRotation();
    glm::vec3 GetLocalRotation() const { return m_transform.m_rotation; }
    void SetRotation(const glm::vec3 rotation) { m_transform.m_rotation = rotation; }
    
    glm::vec3 GetScale();
    glm::vec3 GetLocalScale() const { return m_transform.m_scale; }
    void SetScale(const glm::vec3 scale) { m_transform.m_scale = scale; }
    
    
    Object* GetParent() const { return m_parent; }
    Object* GetRootParent(); 
    void SetParent(Object* object);
    
    std::vector<Object*> GetAllChildren() { return m_children; }
    void RemoveChild(const Object* object);
    
protected:
    void AddChild(Object* object);
};
