#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "../Rendering/Material.h"

namespace ret {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    class Mesh
    {
    public:
        unsigned int VBO, VAO, EBO;
        ret::Material* material = nullptr;

        std::vector<Vertex> vertices_;
        std::vector<unsigned int> indices_;
    public:
        Mesh(const std::vector<Vertex>& vertices,
             const std::vector<unsigned int>& indices,
             Material* mat = nullptr);
        ~Mesh();
        void SetupMesh();
        
    };
}

