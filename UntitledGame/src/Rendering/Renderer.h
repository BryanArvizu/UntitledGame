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

    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        int index;
        Camera* camera = nullptr;
        Shader* defaultShader = nullptr;
        
        static std::vector<Renderer*> renderers;

        std::vector<Model*> models_;
        void Draw();

        bool AddModel(Model* t_modelPtr);
        bool RemoveModel(Model* t_modelPtr);

        void DrawModel(Model* &t_modelPtr);
        void DrawMesh(Mesh mesh, const Transform& transform);
    };
}

