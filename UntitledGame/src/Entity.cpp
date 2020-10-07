#include "Entity.h"

void ret::Entity::StartComponents()
{
    for (unsigned int i = 0; i < components_.size(); i++)
    {
        components_[i]->Start();
    }
}

void ret::Entity::UpdateComponents()
{
    for (unsigned int i = 0; i < components_.size(); i++)
    {
        components_[i]->Update();
    }
}

ret::Entity::Entity() : transform_()
{
    enabled_ = true;
}

bool ret::Entity::AddComponent(Component* component)
{
    for (unsigned int i = 0; i < components_.size(); i++)
    {
        if (component == components_[i])
            return false;
    }
    components_.push_back(component);
    return true;
}

void ret::Entity::Update()
{
    for (unsigned int i = 0; i < components_.size(); i++)
    {
        components_[i]->Update();
    }

    return;
}
