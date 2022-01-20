#pragma once
#include "snuifw/common.h"
#include "snuifw/draw/draw.h"

namespace snuifw
{
    class IDrawContext
    {
        public:
            inline ~IDrawContext() = default;
        
        public:
            // allowed to be called multiple times
            virtual void init() = 0;

            virtual std::string implementationName() = 0;
    };

    class IDrawWindow
    {
        public:
            inline ~IDrawWindow() = default;
        
        public:
            virtual IDrawContext* drawContext() = 0;
    };
}
