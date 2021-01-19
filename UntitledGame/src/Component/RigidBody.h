#pragma once

#include "Component.h"
#include "../Physics/Physics.h"
#include <PxPhysicsAPI.h>

namespace ret {
    class Collider;

    class RigidBody : public Component
    {
    public:
        RigidBody();
        RigidBody(Collider* col);
        ~RigidBody();

        ret::Physics* physicsEngine = nullptr;

        physx::PxShape* shape = nullptr;
        physx::PxMaterial* material = nullptr;
        physx::PxRigidDynamic* dynamic = nullptr;
        physx::PxGeometry* geometry = nullptr;

        void Start() override;
        void Update() override;
    };
}

