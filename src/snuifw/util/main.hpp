#pragma once

#include "snuifw/snuifw.h"

namespace snuifw::util
{
    struct SimpleMainLoop
    {
        Context& context;

        bool running;

        inline SimpleMainLoop(Context& context)
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
