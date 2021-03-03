#include "RigidBody.h"
#include "../RetEngine.h"
#include "Collider.h"
#include <iostream>
#include <PxPhysicsAPI.h>

//ret::DebugRenderer* ret::RigidBody::debugRenderer = nullptr;

ret::RigidBody::RigidBody()
{
    /*if (ret::RigidBody::debugRenderer == nullptr)
    {
        ret::RigidBody::debugRenderer = ret::RetEngine::instance->debugRenderer;
    }*/

    geometry = new physx::PxSphereGeometry(1);
    
    /*if (debugRenderer)
    {
        debugRenderer->AddRigidBody(this);
    }*/

}

ret::RigidBody::RigidBody(Collider* col)
{
    if (col->shape == ret::ColliderShape::SPHERE)
    {
        geometry = new physx::PxSphereGeometry(col->radius);
    }
    else if (col->shape == ret::ColliderShape::CUBE)
    {
        geometry = new physx::PxBoxGeometry(col->halfHeight, col->halfHeight, col->halfHeight);
    }
    else if (col->shape == ret::ColliderShape::CAPSULE)
    {
        geometry = new physx::PxCapsuleGeometry(col->radius, col->halfHeight);
    }
}

ret::RigidBody::~RigidBody()
{
    /*if (debugRenderer)
    {
        debugRenderer->RemoveRigidBody(this);
    }*/
}

void ret::RigidBody::Start()
{
    physicsEngine = ret::RetEngine::Get()->physics;

    if (physicsEngine)
    {
        material = physicsEngine->gMaterial;
        
        dynamic = physx::PxCreateDynamic(*(physicsEngine->gPhysics),
            physx::PxTransform(this->entity->transform.position.x, 
                               this->entity->transform.position.y,
                               this->entity->transform.position.z),
            *geometry,
            *material,
            10.0f);

        dynamic->setAngularDamping(0.5f);
        dynamic->setLinearVelocity(physx::PxVec3(0.0f));

        physicsEngine->gScene->addActor(*dynamic);
    }
}

void ret::RigidBody::Update()
{
    if (physicsEngine)
    {
        physx::PxTransform pose = dynamic->getGlobalPose();

        this->entity->transform.position = glm::vec3(pose.p.x, pose.p.y, pose.p.z);
        this->entity->transform.rotation = glm::quat(pose.q.w, pose.q.x, pose.q.y, pose.q.z);

    }
}
