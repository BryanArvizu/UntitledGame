#pragma once

#include "Window.h"
#include "Entity.h"
#include <vector>

namespace ret {
    class RetEngine
    {
    private:
        ret::Window* window_;
        std::vector<ret::Entity> entities_;
    public:
        RetEngine();
        int Run();
    private:
        void UpdateEntities();
    };
}

