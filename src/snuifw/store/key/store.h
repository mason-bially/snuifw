#pragma once

#include "lager/util.hpp"
#include <immer/box.hpp>
#include <immer/vector.hpp>

#include <variant>

#ifndef HISTORY_SIZE
#define HISTORY_SIZE 10
#endif 

namespace model {
    struct key_event
    {
        int key = 0;
        int scancode = 0;
        int action = 0;
        int modes = 0;
    };

    using b_key = immer::box<key_event>;
    using key_history = immer::vector<immer::box<key_event>>;

    struct KeyModel {
        b_key event;
        key_history undo;
        key_history redo;
    };

    
    struct key_undo {
        size_t nothing;
    };
    struct key_redo {
        size_t nothing;
    };
    struct key_clear {
        size_t nothing;
    };

    using key_action = std::variant<key_event, key_undo, key_redo>;

    inline KeyModel update_key(KeyModel c, key_action action)
    {
        return std::visit(
            lager::visitor{
                [&](key_event a) {
                    c.undo = key_history(c.undo.begin() + (c.undo.size() == HISTORY_SIZE ? 1: 0), c.undo.end());
                    c.undo = c.undo.push_back(c.event);
                    c.redo = key_history();
                    c.event = b_key(a);

                    return c;
                },
                [&](key_undo a) {
                    if(c.undo.size()) {
                        c.redo = c.redo.push_back(c.event);
                        c.event = c.undo.back();
                        c.undo = key_history(c.undo.begin(), c.undo.end() - 1);
                    }
                    return c;
                },
                [&](key_redo a) {
                    if(c.redo.size()) {
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
