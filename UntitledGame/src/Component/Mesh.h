#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "../Shader.h"
#include "../Texture.h"

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
        Shader* shader;
        std::string shaderPath;

        std::vector<Vertex> vertices_;
        std::vector<unsigned int> indices_;
        std::vector<ret::Texture> textures_;
    public:
        Mesh(const std::vector<Vertex>& vertices,
             const std::vector<unsigned int>& indices,
             const std::vector<Texture>& textures);
        ~Mesh();
        void SetupMesh();
        
    };
}

