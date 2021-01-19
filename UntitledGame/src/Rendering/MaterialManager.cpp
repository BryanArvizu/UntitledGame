#include "Material.h"
#include <iostream>

std::unordered_map<std::string, ret::Material> ret::MaterialManager::materials;

ret::Material* ret::MaterialManager::GetMaterial(std::string path)
{
    std::unordered_map<std::string, ret::Material>::iterator iter = materials.find(path);

    if (iter == materials.end())
    {
        Material* mat = new Material();
        iter = materials.insert({ path, *mat }).first;
    }
    else
    {
        std::cout << "\t\t\Texture found :: " << std::endl;
    }

    ret::Material* ptr = &(iter->second);
    return ptr;
}
