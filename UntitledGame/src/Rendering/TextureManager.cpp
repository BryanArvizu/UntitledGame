#include "Texture.h"
#include <iostream>

std::unordered_map<std::string, ret::Texture> ret::TextureManager::textures;

ret::Texture* ret::TextureManager::GetTexture(std::string path, int channels)
{
    std::unordered_map<std::string, ret::Texture>::iterator iter = textures.find(path);

    if (iter == textures.end())
    {
        std::cout << "Texture (" + path + " ) not found :: Adding It" << std::endl;
        iter = textures.insert({ path, ret::Texture::LoadTexture(path, channels) }).first;
        std::cout << "Texture count: " << textures.size() << std::endl;
    }
    else
    {
        std::cout << "\t\t\Texture found :: " << std::endl;
    }

    ret::Texture* ptr = &(iter->second);
    return ptr;
}
