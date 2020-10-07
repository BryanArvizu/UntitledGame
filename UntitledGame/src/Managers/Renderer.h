#pragma once

#include <vector>
#include <string>
#include "../Shader.h"

namespace ret {
    class Mesh;
    class Model;

    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        int index;
        static std::vector<Renderer*> renderers;

        std::vector<ret::Model*> models_;
        void Draw();
        bool AddModel(Model* model);
        bool RemoveModel(Model* model);
        void DrawModel(Model* model);
        void DrawMesh(Mesh mesh);
    };
}

