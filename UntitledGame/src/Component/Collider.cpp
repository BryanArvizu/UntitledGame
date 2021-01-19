#include "Collider.h"

void ret::Collider::SetSphere(float r)
{
    radius = r;
    halfHeight = 0;
    shape = ColliderShape::SPHERE;
}

void ret::Collider::SetCapsule(float h, float r)
{
    halfHeight = h;
    radius = r;
    shape = ColliderShape::CAPSULE;
}

void ret::Collider::setCube(float h)
{
    halfHeight = h;
    shape = ColliderShape::CUBE;
}
