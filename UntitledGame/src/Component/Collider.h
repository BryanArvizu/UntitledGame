#pragma once

#include "Component.h"
#include <glm/glm.hpp>

namespace ret {
    enum class ColliderShape {SPHERE, CAPSULE, CUBE};

    class Collider
    {
    public:

        void SetSphere(float r);
        void SetCapsule(float h, float r);
        void setCube(float h);

        ret::ColliderShape shape = ColliderShape::CUBE;

        glm::vec3 origin = glm::vec3(0);
        float halfHeight = 1;
        float radius = 1;
    };
}

