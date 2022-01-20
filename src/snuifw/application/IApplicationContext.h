#pragma once

#include "application.h"

namespace snuifw
{
    class IApplicationWindow
    {
        public:
            struct WindowDescription
            {
                uint16_t width = 640, height = 480;
                int32_t xpos = std::numeric_limits<int32_t>::min(), ypos = std::numeric_limits<int32_t>::min();
                std::string title = "SNUIFW Application";
            };

        public:
            ~IApplicationWindow();
        
        public:
            WindowDescription const& description() const;
    };
}
