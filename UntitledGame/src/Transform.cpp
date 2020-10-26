#include "Transform.h"

ret::Transform::Transform(glm::vec3 t_pos) 
    : position(t_pos), scale(0.0f), worldPosition(glm::vec3(0))
{
    entity = nullptr;
    parent = nullptr;
}

ret::Transform::Transform(Entity* t_entity, glm::vec3 t_pos)
    : position(t_pos), scale(0.0f), worldPosition(glm::vec3(0)), entity(t_entity)
{
    parent = nullptr;
}
