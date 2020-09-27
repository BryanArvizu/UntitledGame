#pragma once

#include <string>

struct GLFWwindow;

namespace ret {
    class Window
    {
    private:
        GLFWwindow* window_;
        int windowWidth_, windowHeight_;
    public:
        Window(int t_width = 1280, int t_height = 720, std::string t_name = "My Window");

    };
}

