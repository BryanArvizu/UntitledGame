#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

namespace ret {
    class Entity;

    class Transform
    {
    public:
        Entity* entity;

        glm::vec3 position;
        glm::quat rotation = glm::quat();
        glm::vec3 scale;

        Transform* parent;
        std::vector<Transform*> children;

    private:
        glm::vec3 worldPosition;
    public:
        Transform(glm::vec3 t_pos = glm::vec3(0,0,0));
        Transform(Entity* t_entity, glm::vec3 t_pos = glm::vec3(0, 0, 0));
    };
}

