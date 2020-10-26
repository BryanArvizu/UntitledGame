#include "TextureManager.h"
#include <iostream>

std::unordered_map<std::string, ret::Texture> ret::TextureManager::textures;

ret::Texture* ret::TextureManager::GetTexture(std::string path)
{
    std::unordered_map<std::string, ret::Texture>::iterator iter = textures.find(path);

    if (iter == textures.end())
    {
        std::cout << "Shader (" + path + " ) not found :: Adding It" << std::endl;
        iter = textures.insert({ path, ret::Texture::LoadTexture(path) }).first;
        std::cout << "Shader count: " << textures.size() << std::endl;
    }
    else
    {
        std::cout << "\t\t\tShader found :: " << std::endl;
    }

    ret::Texture* ptr = &(iter->second);
    return ptr;
}
