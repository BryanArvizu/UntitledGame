#pragma once

namespace ret {
    class Component
    {
    public:
        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void FixedUpdate() = 0;
    };
}

