#pragma once

#include <vector>

namespace ret {
    class Watcher
    {
    public:
        Watcher(void* t_ptr) : ptr(t_ptr) {}
        ~Watcher()
        {
            for (auto pointer : watched)
            {
                if (*pointer == ptr)
                    *pointer = nullptr;
            }
        }

        template <class T>
        void FetchPointer(T* &t_ptr)
        {
            void** temp_ptr = (void**)&t_ptr;
            watched.push_back(temp_ptr);
            t_ptr = (T*)ptr;
        }
    private:
        void* ptr;
        std::vector<void**> watched;
    };
}

