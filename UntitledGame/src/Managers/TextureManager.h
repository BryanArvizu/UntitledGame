#pragma once

#include <unordered_map>
#include "../Texture.h"
#include "../stb_image.h"

namespace ret {
    class TextureManager
    {
    public:
        static std::unordered_map<std::string, Texture> textures;
        static Texture* GetTexture(std::string path);
    };
}

