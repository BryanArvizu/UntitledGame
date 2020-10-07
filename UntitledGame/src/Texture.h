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
        void LoadTexture(std::string address, GLenum format);
        void Use();
        unsigned int GetID() const { return id; }
    };
}

