#pragma once

namespace ret {
    class Entity;

    class Component
    {
    public:
        Entity* entity;
        bool enabled;
    public:
        virtual void Start() {};
        virtual void Update() {};
        virtual void FixedUpdate() {};
    };
}

