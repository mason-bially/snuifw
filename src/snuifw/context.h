
#pragma once
#include "common.h"

#include "store/store.hpp"

namespace snuifw {


    class Context 
    {
    public:
        //TODO template this
        model::Model _model;
        GrContext* sContext = nullptr;
        SkSurface* sSurface = nullptr;
    public:
        
        virtual void init();
        virtual void teardown();
        virtual bool is_running();
        virtual void wait_events();
    private:
        void init_glfw();
        void init_skia();
        void fill_window_events();
        void dispatch(model::action);

    public:
        GLFWwindow* window_weak_ref();

    private:
        void keyCallback(GLFWwindow* w,int k,int s,int a, int m);
        void windowFocusCallback(GLFWwindow* w, int i);
        void framebufferResizeCallback(GLFWwindow *c, int w, int h);
    };
}