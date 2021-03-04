#pragma once

#include "Transform.h"
#include "Component/Component.h"
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <cereal/types/vector.hpp>
#include "Watcher.h"

namespace ret {
    class Entity
    {
    public:
        uint32_t id = lastId++;
        std::string name;
        bool enabled;

        ret::Watcher watcher;

        ret::Transform transform;
        std::vector<Component*> components_;
    private:
        static uint32_t lastId;

        void StartComponents();
        void UpdateComponents();
        
    public:
        Entity();
        ~Entity();

        bool AddComponent(Component* component);
        bool RemoveComponent(Component* component);
        void Update();
        
        template<class T> void GetComponent(T* &t_ptr);
    };



    template<class T>
    void Entity::GetComponent(T* &t_ptr)
    {
        for (unsigned int i = 0; i < components_.size(); i++)
        {
            if (typeid(T) == typeid(*components_[i]))
            {
                std::cout << "MATCHING TYPE" << std::endl;
                components_[i]->watcher.FetchPointer<T>(t_ptr);
                return;
            }
        }
        t_ptr = nullptr;
    }
}

