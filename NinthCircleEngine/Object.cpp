#include "Object.h"


Object::~Object()
{
    for (Object* const& child : m_children)
        delete child;
}

Transform Object::GetTransform() const { return m_parent ? m_parent->GetTransform() + GetLocalTransform() : GetLocalTransform(); }
glm::vec3 Object::GetPosition()  const { return m_parent ? m_parent->GetPosition()  + GetLocalPosition()  : GetLocalPosition(); }
glm::vec3 Object::GetRotation()  const { return m_parent ? m_parent->GetRotation()  + GetLocalRotation()  : GetLocalRotation(); }
glm::vec3 Object::GetScale()     const { return m_parent ? m_parent->GetScale()     + GetLocalScale()     : GetLocalScale(); }


Object* Object::GetRootParent() { return m_parent ? m_parent->GetRootParent() : this; }


void Object::SetParent(Object* object)
{
    if (m_parent) { m_parent->RemoveChild(this); }
    
    object->AddChild(this);
    m_parent = object;
}

void Object::AddChild(Object* object)
{
    m_children.emplace_back(object);
}

void Object::RemoveChild(const Object* object)
{
    for (size_t i = 0; i < m_children.size(); ++i)
    {
        if (m_children[i] == object)
        {
            m_children[i]->SetParent(nullptr);
            m_children.erase(m_children.begin() + i);
            return;
        }
    }
}