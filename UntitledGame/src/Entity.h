#pragma once

#include "Transform.h"
#include "Component/Component.h"
#include <vector>
#include <string>
#include <fstream>
#include <cereal/types/vector.hpp>

namespace ret {
    class Entity
    {
    public:
        std::string name;
        bool enabled;

        ret::Transform transform;
        std::vector<ret::Component*> components_;
    private:
        void StartComponents();
        void UpdateComponents();
        
    public:
        Entity();
        ~Entity();

        bool AddComponent(Component* component);
        bool RemoveComponent(Component* component);
        void Update();
        
        template<class T> T* GetComponent();
    };






    template<class T>
    T* Entity::GetComponent()
    {
        for (unsigned int i = 0; i < components_.size(); i++)
        {
            if (typeid(T) == typeid(*components_[i]))
                return dynamic_cast<T*>(components_[i]);
        }
        return nullptr;
    }
}

