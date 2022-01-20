
#pragma once
#include "common.h"

namespace snuifw
{

    class TopContext 
    {
    private:
        bool _canceled = false;
        bool _inMain = false;

        friend class Context;
        std::vector<class Context*> _contexts;

    public:
        void init();
        void teardown();
        bool isRunning();
        void shutdown();
        void main(); // takes control until canceled

        std::function<void ()> loop; // not rate limited

        void update_all();

    private:
        void _initGlfw();
        void _initSkia();
    };
}
