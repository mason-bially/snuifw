#pragma once

#include "snuifw/snuifw.h"

namespace snuifw::util
{
    struct SimpleMainLoop
    {
        TopContext& context;

        bool running;

        inline SimpleMainLoop(TopContext& context)
            : context(context)
            , running(false)
        {

        }

        inline void main_loop()
        {
            running = true;
            while (running)
            {
                context.update_all();
            }
        }
    };
}
