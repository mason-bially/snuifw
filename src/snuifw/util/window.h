#pragma once

#include "snuifw/common.h"

namespace snuifw {
namespace util
{
    class WindowContainer
    {
        GLFWwindow* _window;
        public:
            inline WindowContainer(GLFWwindow* window): _window(window) {};
            inline ~WindowContainer(){ if(_window){glfwDestroyWindow(_window);}}

            inline GLFWwindow* window() {return _window;}
    };
}}