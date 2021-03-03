#pragma once

#include <unordered_map>

namespace ret {
    template<class T>
    class Manager
    {
        Manager() = default;

        std::unordered_map<std::string, T> contents;

        T* Get(std::string key);
        T* Create(std::string key);
        T* Fetch(std::string key);
    };

    template<class T>
    inline T* Manager<T>::Get(std::string key)
    {
        auto iter = contents.find(key);

        if (iter != contents.end())
        {
            return iter->second;
        }
        return nullptr;
    }

    template<class T>
    inline T* Manager<T>::Create(std::string key)
    {
        auto result = contents.try_emplace(key, T());
        return nullptr;
    }

    template<class T>
    inline T* Manager<T>::Fetch(std::string key)
    {
        auto result = contents.emplace(key, T());
        if (result.second == true)
        {
            return result.first.first;
        }
        return nullptr;
    }

}

