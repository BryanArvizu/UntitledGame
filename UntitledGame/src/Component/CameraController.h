#pragma once
#include "Component.h"
#include "../Camera.h"

struct GLFWwindow;

namespace ret {
    class CameraController : public Component
    {
    public:
        GLFWwindow* window = nullptr;
        std::weak_ptr<Component> comp = {};
        Camera* camera = nullptr;
    public:
        void Start() override;
        void Update() override;
    private:
        void UpdateMovement();
        void UpdateCamera();
    };
}

