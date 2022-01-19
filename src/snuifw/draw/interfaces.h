#pragma once
#include "snuifw/common.h"
#include "snuifw/draw/draw.h"

namespace snuifw
{
    class IDrawLayer
    {
        public:
            ~IDrawLayer();
        
        public:
            // allowed to be called multiple times
            virtual void init() = 0;

            virtual std::string implementationName() = 0;
    };
}
