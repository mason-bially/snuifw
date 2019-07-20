#pragma once

#include "lager/util.hpp"
#include <variant>

namespace model {

struct Window {
    int x = 0;
    int y = 0;
    int width = 960;
    int height = 640;

    std::string name = "Hello World";
};

struct Model
{
    Window window;
    int zoom_value = 0;
};

struct zoom_action
{
    int direction = 0;
};

using action = std::variant<zoom_action>;

inline Model update(Model c, action action)
{
    return std::visit(
        lager::visitor{
            [&](zoom_action a) { return Model {
                std::min(15, std::max(0, a.direction))
            };},
        },
        action);
}

} // namespace counter
