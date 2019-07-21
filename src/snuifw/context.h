
#pragma once
#include "common.h"

#include "store/store.hpp"

namespace snuifw {

    class Context 
    {
    private:
        //TODO template this
        model::Model _model;

        GrContext* _context = nullptr;
        GrGLFramebufferInfo _frameBuffer;
        GrBackendRenderTarget _renderTarget;
        SkSurface* _surface = nullptr;

        bool _canceled = false;
        bool _inMain = false;

    public:
        inline SkSurface* getSurface() { return _surface; };
        inline model::Model& getModel() { return _model; };
        GLFWwindow* getWindow();

    public:
        void init();
        void teardown();
        bool isRunning();
        void close();
        void main(); // takes control until canceled

        std::function<void ()> loop; // not rate limited

    public:
        void swap(); // is vsync right now
        void dispatch(model::action);

    private:
        void _initGlfw();
        void _initSkia();
        void _fillWindowEvents();

        bool _rebuildSurface(int w, int h);

    private:
        void _keyCallback(GLFWwindow* w,int k,int s,int a, int m);
        void _windowFocusCallback(GLFWwindow* w, int i);
        void _windowRefreshCallback(GLFWwindow* w);
        void _framebufferResizeCallback(GLFWwindow *c, int w, int h);
    };
}
