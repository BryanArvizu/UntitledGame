#pragma once

#include <string>
#include <unordered_map>
#include <glad/glad.h>

namespace ret {
    class Texture
    {
    public:
        static unsigned int texCount;
        unsigned int id = 0;
        std::string type;
        std::string path;
    public:
        static Texture LoadTexture(const std::string &path, int channels = 4);
    };

    // TEXTURE MANAGER for getting textures and making sure they are only created once and reused
    class TextureManager
    {
    public:
        static std::unordered_map<std::string, Texture> textures;
        static Texture* GetTexture(std::string path, int channels = 4);
    };
}

