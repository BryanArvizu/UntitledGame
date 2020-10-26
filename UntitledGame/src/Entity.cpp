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

ret::Entity::Entity() : transform(ret::Transform(this))
{
    enabled = true;
}

ret::Entity::~Entity()
{
    
}

bool ret::Entity::AddComponent(Component* component)
{
    for (unsigned int i = 0; i < components_.size(); i++)
    {
        if (component == components_[i])
            return false;
    }
    components_.push_back(component);
    component->entity = this;
    return true;
}

bool ret::Entity::RemoveComponent(Component* component)
{
    for (unsigned int i = 0; i < components_.size(); i++)
    {
        if (component == components_[i])
        {
            components_[i]->entity = nullptr;
            components_.erase(components_.begin()+i);
            return true;
        }
    }
    return false;
}

void ret::Entity::Update()
{
    for (unsigned int i = 0; i < components_.size(); i++)
    {
        components_[i]->Update();
    }
}
