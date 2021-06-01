#pragma once

#include "snuifw/util/helpers.hpp"

#include "snuifw/store/window/store.hpp"
#include "snuifw/store/key/store.hpp"

namespace snuifw::model {

    struct Model
    {
        window::Model window;
        key::Model key;
    };

    struct zoom_action
    {
        int direction = 0;
    };



    using action = std::variant<key::action, window::action>;

    inline Model update(Model c, action action)
    {
        return std::visit(
            util::visitor{
                [&](window::action a) { c.window = update_window(c.window, a); return c;},
                [&](key::action a) { c.key = update_key(c.key, a); return c;},
            },
            action);
    }

} // namespace snuifw::model
