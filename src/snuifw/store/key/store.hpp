#pragma once

#include "immer/box.hpp"
#include "immer/vector.hpp"

#include "snuifw/common.h"
#include "snuifw/util/util.h"

namespace snuifw::model::key
{
    const size_t c_historySize = 10;

    struct event
    {
        int key = 0;
        int scancode = 0;
        int action = 0;
        int modes = 0;
    };

    using b_key = immer::box<event>;
    using key_history = immer::vector<immer::box<event>>;

    struct Model
    {
        b_key event;
        key_history undo;
        key_history redo;
    };

    
    struct a_undo { size_t nothing; };
    struct a_redo { size_t nothing; };
    struct a_clear { size_t nothing; };

    using action = std::variant<event, a_undo, a_redo>;

    inline Model update_key(Model c, action action)
    {
        return std::visit(
            util::visitor{
                [&](event a)
                {
                    c.undo = key_history(c.undo.begin() + (c.undo.size() == c_historySize ? 1: 0), c.undo.end());
                    c.undo = c.undo.push_back(c.event);
                    c.redo = key_history();
                    c.event = b_key(a);

                    return c;
                },
                [&](a_undo a)
                {
                    if(c.undo.size())
                    {
                        c.redo = c.redo.push_back(c.event);
                        c.event = c.undo.back();
                        c.undo = key_history(c.undo.begin(), c.undo.end() - 1);
                    }
                    return c;
                },
                [&](a_redo a)
                {
                    if(c.redo.size())
                    {
                        c.undo = c.undo.push_back(c.event);
                        c.event = c.redo.back();
                        c.redo = key_history(c.redo.begin(), c.redo.end() - 1);
                    }
                    return c;
                },
            },
            action);
    }

}
