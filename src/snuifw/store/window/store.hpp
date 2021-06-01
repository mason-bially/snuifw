#pragma once

#include "snuifw/common.h"
#include "snuifw/util/window.h"
#include "snuifw/util/helpers.hpp"


namespace snuifw::model::window
{
    struct Model
    {
        std::shared_ptr<snuifw::util::WindowContainer> window;
        snuifw::util::WindowEvents events;

        int x = 0;
        int y = 0;
        bool focused = true;
        int width = 960;
        int height = 640;
        std::string name = "Hello World";
    };


    struct a_focused
    {
        bool focused;
    };

    struct a_resized
    {
        int w;
        int h;
    };

    struct a_events
    {
        snuifw::util::WindowEvents events;
    };

    struct a_name
    {
        std::string name;
    };

    struct a_window
    {
        std::shared_ptr<snuifw::util::WindowContainer> window;
    };


    using action = std::variant<
        a_focused,
        a_resized, 
        a_events,
        a_name,
        a_window
    >;

    inline Model update_window(Model c, action action)
    {
        return std::visit(
            util::visitor{
                [&](a_name a) { c.name = a.name; return c;},
                [&](a_window a) { c.window = a.window; return c;},
                [&](a_focused a) { c.focused = a.focused; return c;},
                [&](a_resized a)
                { 
                    c.width = a.w; c.height = a.h; 
                    return c;
                },
                [&](a_events a)
                {
                    c.events = a.events;
                    return c;
                } 
            },
            action);
    }

}
