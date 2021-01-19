#include "Physics.h"

//#include <PxPhysicsAPI.h>

#include <iostream>

ret::Physics::Physics()
{
    InitalizePhysics();
}

ret::Physics::~Physics()
{
    gScene->release();
    gDispatcher->release();
    gPhysics->release();
    gPvd->release();
    gFoundation->release();
}

void ret::Physics::Update(bool interactive)
{
    if (gScene != nullptr)
    {
        PX_UNUSED(interactive);
        gScene->simulate(1.0f / 60.0f); // 60 ticks per second
        gScene->fetchResults(true);
    }
}

void ret::Physics::InitalizePhysics(bool interactive)
{
    gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
    if (!gFoundation)
    {
        std::cout << "PxCreateFoundation Failed" << std::endl;
        return;
    }
    gPvd = PxCreatePvd(*gFoundation);
    gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, physx::PxTolerancesScale(), true, gPvd);

    physx::PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    gDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = gDispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    gScene = gPhysics->createScene(sceneDesc);

    gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
    physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*gPhysics, physx::PxPlane(0, 1, 0, 0), *gMaterial);
    //physx::PxRigidStatic* groundPlane = physx::PxCreateStatic(*gPhysics, physx::PxTransform(0, 1, 0), physx::PxPlaneGeometry(), *gMaterial);
    gScene->addActor(*groundPlane);
}
