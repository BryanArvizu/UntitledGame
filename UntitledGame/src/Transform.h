#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace ret {
    class Entity;

    class Transform
    {
    public:
        glm::vec3 position;
        // glm::vec3 rotation;
        glm::vec3 scale;

        Transform* parent;
        std::vector<Transform> children;

        Entity* entity;
    private:
        glm::vec3 worldPosition;
    public:
        Transform(glm::vec3 t_pos = glm::vec3(0,0,0));
        Transform(Entity* t_entity, glm::vec3 t_pos = glm::vec3(0, 0, 0));
    };
}

