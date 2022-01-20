#pragma once

#include "input.h"

namespace snuifw
{
    // Input layers are for users to register their input handling stratagies
    class IInputLayer
    {
        public:
            inline ~IInputLayer() = default;
        

        public:
            inline virtual bool input_windowFocus() { return false; }
            inline virtual bool input_keyboardKey() { return false; }
            inline virtual bool input_textChar() { return false; }
            inline virtual bool input_mouseMove(double x, double y) { return false; }
            inline virtual bool input_mouseClick() { return false; }
    };
}
