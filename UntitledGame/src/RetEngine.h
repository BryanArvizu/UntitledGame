#pragma once

#include "Window.h"
#include "Scene.h"
#include "Entity.h"
#include "Rendering/Renderer.h"
#include "Physics/PhysicsEngine.h"
#include <vector>
#include <memory>

namespace ret {
    class RetEngine
    {
    public:
        std::unique_ptr<ret::Window> window_;
        ret::Renderer* renderer = nullptr;
        ret::PhysicsEngine* physics = nullptr;
        std::vector<ret::Scene> scenes_;

        static RetEngine* instance;
    private:
        double accumulator = 0.0f;
        double fixedAccumulator = 0.0f;
    public:
        static int Start();
        static RetEngine* Get() { return instance; }
    private:
        int Run();

        RetEngine();
        ~RetEngine();

        ret::Scene& CreateScene();
    };
}

