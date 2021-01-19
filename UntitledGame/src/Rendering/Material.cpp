#include "Material.h"

ret::Material::Material(std::string shaderPath)
{
    shader = ret::ShaderManager::GetShader(shaderPath);
}
