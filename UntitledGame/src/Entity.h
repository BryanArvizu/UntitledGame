#pragma once

#include "Transform.h"
#include "Component.h"
#include <vector>

namespace ret {
    class Entity
    {
    private:
        bool enabled_;
        ret::Transform transform_;
        std::vector<ret::Component> components_;
    private:
        void StartComponents();
        void UpdateComponents();
    public:
        Entity();
        bool isEnabled() { return enabled_; }
        void Update();
    };
}

