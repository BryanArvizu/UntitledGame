#pragma once
#include <string>
#include <glad/glad.h>

namespace ret {
    class Texture
    {
    public:
        static unsigned int texCount;
        unsigned int id;
        std::string type;
        std::string path;
    public:
        static Texture LoadTexture(const std::string &path, int channels = 4);
    };
}

