#include "Scene.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cereal/archives/json.hpp>


ret::Scene::~Scene()
{
    for (auto& ptr : entities_)
    {
        if (ptr == nullptr)
            continue;
        ptr->name = "Deleted";
        delete ptr;
        ptr = nullptr;
    }
}

void ret::Scene::UpdateEntities()
{
    for (unsigned int i = 0; i < entities_.size(); i++)
    {
        if (entities_[i]->enabled == true)
            entities_[i]->Update();
    }
}

void ret::Scene::Save(std::string path)
{
    //std::ofstream file(path);

    //if (file.is_open())
    //{
    //    cereal::JSONOutputArchive oarchive(file);

    //    serialize(oarchive);
    //}

    //file.close();

}

void ret::Scene::Load(std::string path)
{
    //std::ifstream file(path);

    //if (file.is_open())
    //{
    //    cereal::JSONInputArchive iarchive(file);

    //    serialize(iarchive);
    //}

    //file.close();
}


