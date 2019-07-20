// //
// // lager - library for functional interactive c++ programs
// // Copyright (C) 2017 Juan Pedro Bolivar Puente
// //
// // This file is part of lager.
// //
// // lager is free software: you can redistribute it and/or modify
// // it under the terms of the MIT License, as detailed in the LICENSE
// // file located at the root of this source code distribution,
// // or here: <https://github.com/arximboldi/lager/blob/master/LICENSE>
// //

// #include "lager/util.hpp"
// #include <variant>

// namespace model {


// struct model
// {
//     int zoom_value = 0;
// };

// struct zoom_action
// {
//     int direction = 0;
// };

// using action = std::variant<zoom_action>;

// model update(model c, action action)
// {
//     return std::visit(
//         lager::visitor{
//             [&](zoom_action a) { return model{
//                 std::min(15, std::max(0, a.direction));
//             };},
//         },
//         action);
// }

// } // namespace counter
