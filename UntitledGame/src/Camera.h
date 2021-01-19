#pragma once

#include "Component/Component.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace ret {
    class Camera : public Component
    {
    public:
        glm::vec3 posOffset;
        glm::vec3 rotation;
        float fov = 90.0f;
    
        glm::vec3 front_;
        glm::vec3 up_;
        glm::vec3 right_;
        glm::vec3 worldUp_;
    public:
        Camera(glm::vec3 t_pos = glm::vec3(0,0,0), glm::vec3 t_rot = glm::vec3(0, 0, 0));
        glm::mat4 GetViewMatrix();
        void Rotate(float t_xoffset, float t_yoffset, GLboolean t_constrainPitch);
    private:
        void UpdateCameraVectors();
    };
}

