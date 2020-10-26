#pragma once

#include "Window.h"
#include "Scene.h"
#include "Entity.h"
#include "Managers/Renderer.h"
#include <vector>

namespace ret {
    class RetEngine
    {
    private:
        ret::Window* window_;
        ret::Renderer renderer;
        std::vector<ret::Scene> scenes_;
    public:
        RetEngine();
        ~RetEngine();
        int Run();
    private:
        void UpdateScenes();
    };
}

