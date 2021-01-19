#pragma once

#include "Shader.h"
#include "Texture.h"

#include <vector>
#include <string>

namespace ret {
    class Material
    {
    public:
        Material() = default;
        Material(std::string shaderPath);

        Shader* shader = nullptr;
        std::vector<ret::Texture*> textures;
    };

    class MaterialManager
    {
    public:
        static std::unordered_map<std::string, Material> materials;
        static Material* GetMaterial(std::string path);
    };
}

