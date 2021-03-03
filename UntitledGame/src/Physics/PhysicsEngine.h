#pragma once

#include <PxPhysicsAPI.h>

namespace ret {
    class PhysicsEngine
    {
    public:
        
        physx::PxReal stackZ = 10.0f;

        physx::PxDefaultAllocator gAllocator;
        physx::PxDefaultErrorCallback gErrorCallback;

        physx::PxDefaultCpuDispatcher* gDispatcher = nullptr;
        physx::PxScene* gScene = nullptr;

        physx::PxMaterial* gMaterial = nullptr;

        physx::PxFoundation* gFoundation = nullptr;
        physx::PxPhysics* gPhysics = nullptr;
        physx::PxPvd* gPvd = nullptr;

        PhysicsEngine();
        ~PhysicsEngine();

        void Update(bool interactive = true);
    private:
        void InitalizePhysics(bool interactive = true);
        physx::PxRigidDynamic* CreateDynamic(const physx::PxTransform& t, const physx::PxGeometry& geometry, const physx::PxVec3& velocity = physx::PxVec3(0));
        void createStack(const physx::PxTransform& t, physx::PxU32 size, physx::PxReal halfExtent);
    };

}

