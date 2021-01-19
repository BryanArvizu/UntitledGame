#include "Model.h"
#include <iostream>

std::unordered_map<std::string, ret::Model> ret::ModelManager::models;

ret::Model* ret::ModelManager::GetModel(std::string path)
{
    std::unordered_map<std::string, ret::Model>::iterator iter = models.find(path);

    if (iter == models.end())
    {
        Model* model = new Model(path);
        iter = models.insert({ path, *model }).first;
    }
    else
    {

    }

    ret::Model* ptr = &(iter->second);
    return ptr;
}