#pragma once

#include "Entity.h"
#include <string>
#include <cereal/types/vector.hpp>

namespace ret {
    class Scene
    {
    public:
        std::string name = "";
        std::vector<ret::Entity*> entities_;
    public:
        Scene() {};
        ~Scene();
        void UpdateEntities();

        void Save(std::string path);
        void Load(std::string path);
    };
}

