#pragma once

#include "lager/util.hpp"


#include <variant>

namespace model {
    struct WindowModel {
        int x = 0;
        int y = 0;
        int width = 960;
        int height = 640;

        std::string name = "Hello World";
    };

    struct window_name_action {
        std::string name;
    };


    using window_action = std::variant<window_name_action>;

    inline WindowModel update_window(WindowModel c, window_action action)
    {
        return std::visit(
            lager::visitor{
                [&](window_name_action a) { WindowModel res(c); res.name = a.name; return res;}   
            },
            action);
    }

}
