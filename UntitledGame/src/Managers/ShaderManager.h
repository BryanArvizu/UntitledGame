#pragma once

#include <string>
#include <unordered_map>
#include "../Shader.h"

namespace ret {
    class ShaderManager
    {
    public:
        static std::unordered_map<std::string, Shader> shaders;
        static Shader* GetShader(std::string path);
    };
}

