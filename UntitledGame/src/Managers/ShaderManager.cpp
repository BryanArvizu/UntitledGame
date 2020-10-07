#include "ShaderManager.h"
#include <iostream>

std::unordered_map<std::string, ret::Shader> ret::ShaderManager::shaders;

ret::Shader* ret::ShaderManager::GetShader(std::string path)
{
    std::unordered_map<std::string, Shader>::iterator iter = shaders.find(path);

    if (iter == shaders.end())
    {
        std::cout << "Shader (" + path + " ) not found :: Adding It" << std::endl;
        iter = shaders.insert({ path, Shader((path + ".vert").c_str(), (path + ".frag").c_str()) }).first;
        std::cout << "Shader count: " << shaders.size() << std::endl;
    }
    else
    {
        std::cout << "\t\t\tShader found :: " << std::endl;
    }
    
    Shader* ptr = &(iter->second);
    return ptr;
}
