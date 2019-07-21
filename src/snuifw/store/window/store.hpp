#pragma once

#include "lager/util.hpp"


#include <variant>

namespace model {

    class WindowContainer
    {
        GLFWwindow* _window;
        public:
            inline WindowContainer(GLFWwindow* window): _window(window) {};
            inline ~WindowContainer(){ if(_window){glfwDestroyWindow(_window);}}

            inline GLFWwindow* window() {return _window;}
    };

    struct WindowModel {
        std::shared_ptr<WindowContainer> window;
        
        int x = 0;
        int y = 0;
        bool focused = true;
        int width = 960;
        int height = 640;

        std::string name = "Hello World";
    };


    struct window_focused {
        bool focused;
    };

    struct window_resized {
        int w;
        int h;
    };

    struct window_name_action {
        std::string name;
    };

    struct set_window_action {
        std::shared_ptr<WindowContainer> window;
    };


    using window_action = std::variant<
        window_name_action, 
        set_window_action,
        window_resized,
        window_focused
    >;

    inline WindowModel update_window(WindowModel c, window_action action)
    {
        return std::visit(
            lager::visitor{
                [&](window_name_action a) { c.name = a.name; return c;},
                [&](set_window_action a) { c.window = a.window; return c;},
                [&](window_focused a) { c.focused = a.focused; return c;},
                [&](window_resized a) { 
                    c.width = a.w; c.height = a.h; 
                    return c;
                },
            },
            action);
    }

}
