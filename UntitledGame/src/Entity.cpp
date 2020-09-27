#include "Entity.h"

void ret::Entity::StartComponents()
{
    for (unsigned int i = 0; i < components_.size(); i++)
    {
        components_[i].Start();
    }
}

void ret::Entity::UpdateComponents()
{
    for (unsigned int i = 0; i < components_.size(); i++)
    {
        components_[i].Update();
    }
}

ret::Entity::Entity()
{
    enabled_ = true;
}

void ret::Entity::Update()
{
    

    return;
}
