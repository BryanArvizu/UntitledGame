#pragma once

#include "../RetEngine.h"
#include "Component.h"
#include "Model.h"
#include "../Rendering/Material.h"

namespace ret {
    class Render : public Component
    {
    public:
        Render() = default;

        uint8_t layer = 0x00;
        Model* model = nullptr;
        Material* mat = nullptr;

        void Start() override;
    };
}

