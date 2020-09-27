#include "Window.h"

#include <GLFW/glfw3.h>
#include <iostream>

ret::Window::Window(int t_width, int t_height, std::string t_name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowWidth_ = t_width;
    windowHeight_ = t_height;

    window_ = glfwCreateWindow(windowWidth_, windowHeight_, t_name.c_str(), NULL, NULL);

    if (window_ == NULL)
    {
        std::cout << "RETENGINE::WINDOW::FAILURE -> \"Failed to Create Window\"" << std::endl;
    }

    glfwSetWindowUserPointer(window_, this);
    glfwMakeContextCurrent(window_);

    glViewport(0, 0, windowWidth_, windowHeight_);
}
