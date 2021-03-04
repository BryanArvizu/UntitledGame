#pragma once

#include <vector>
#include <string>
#include <memory>
#include "../Rendering/Shader.h"

namespace ret {
    class Mesh;
    class Model;
    class Camera;
    class Entity;
    class Transform;
    class Render;
    class Material;

    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        Camera* camera = nullptr;
        Shader* defaultShader = nullptr;

        std::vector<Render*> renderList;
        void Draw();

        bool Add(Render* t_renderPtr);
        bool Remove(Render* t_renderPtr);

        void DrawModel(const Model* t_modelPtr, const Transform &t_transform, const Material* t_material);
        void DrawMesh(const Mesh &mesh, const Transform& transform, const Material* &t_material);
    };
}

