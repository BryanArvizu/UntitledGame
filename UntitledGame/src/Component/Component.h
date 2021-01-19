#pragma once
#include <memory>
#include "../Watcher.h"

namespace ret {
    class Entity;

    class Component
    {
    public:
        Entity* entity;
        bool enabled = true;
        ret::Watcher watcher = {this};
    protected:
        bool startCalled = false, onEnableCalled = false, onDisableCalled = false;

        virtual void Start() {};

        virtual void OnEnable() {};
        virtual void OnDisable() {};

        virtual void Update() {};
        virtual void PostUpdate() {};
        virtual void FixedUpdate() {};

        void Updater()
        {
            if (!onEnableCalled && enabled)
            {
                onEnableCalled = true;
                OnEnable();
            }
            else if (!enabled && !onDisableCalled)
            {
                onDisableCalled = true;
                OnDisable();
            }

            if (!startCalled)
            {
                startCalled = true;
                Start();
            }

            if (enabled)
            {
                Update();
                PostUpdate();
            }
        }

        friend class Entity;
    };
}

