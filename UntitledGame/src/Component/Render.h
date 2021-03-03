#pragma once

#include "Component.h"
#include "Model.h"
#include "../Rendering/Material.h"

namespace ret {
    class Render : public Component
    {
    public:
        uint8_t layer = 0x00;
        Model* model;
        Material* mat;
    };
}

