#pragma once

#include "lager/util.hpp"
#include <variant>

#include "window/store.h"
#include "key/store.h"

namespace model {



struct Model
{
    WindowModel window;
    KeyModel key;
};

struct zoom_action
{
    int direction = 0;
};



using action = std::variant<key_action, window_action>;

inline Model update(Model c, action action)
{
    return std::visit(
        lager::visitor{
            [&](window_action a) { c.window = update_window(c.window, a); return c;},
            [&](key_action a) { c.key = update_key(c.key, a); return c;}  
        },
        action);
}

} // namespace counter
