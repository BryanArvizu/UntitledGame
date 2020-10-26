#pragma once

#include "Entity.h"
#include <string>
#include <cereal/types/vector.hpp>

namespace ret {
    class Scene
    {
    public:
        std::string name;
        std::vector<ret::Entity> entities_;
    public:
        Scene() = default;
        void UpdateEntities();

        void Save(std::string path);
        void Load(std::string path);

        //template<class Archive>
        //void serialize(Archive& archive)
        //{
        //    archive(CEREAL_NVP(name), CEREAL_NVP(entities_));
        //}
    };
}

