#pragma once

#include <glm/glm.hpp>

namespace ret {
    class Transform
    {
    public:
        glm::vec3 position;
        float scale;
    public:
        Transform();
    };
}

