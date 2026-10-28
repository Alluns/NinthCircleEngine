#pragma once
#include <glm/vec3.hpp>


class Transform
{
public:
    glm::vec3 aPosition;
    glm::vec3 aRotation;
    glm::vec3 aScale;
    
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
};
