#pragma once
#include "snuifw/common.h"
#include "snuifw/literal/literal.h"

namespace snuifw::literal
{
    struct ScreenPair
    {
        float x;
        float y;
    };

    struct ScreenRect
    {
        float left;
        float right;
        float top;
        float bottom;
    };
}
