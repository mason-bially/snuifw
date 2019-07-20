
#pragma once
#include "common.h"

#include "store.hpp"

namespace snuifw {


    class Context 
    {
    public:
        GLFWwindow* window;
        //TODO template this
        model::Model _model;
        GrContext* sContext = nullptr;
        SkSurface* sSurface = nullptr;
    public:
        


        virtual void init();
        virtual void teardown();

        virtual bool is_running();
    };
}