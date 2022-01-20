#pragma once

#include "draw.h"
#include "snuifw/TopContext.h"

namespace snuifw::skia
{
    class DrawContext
        : IDrawContext
    {
        TopContext _top;
    };

    class DrawWindow
        : IDrawWindow
    {
        class snuifw::Context* _snuifw;
        friend class snuifw::Context;

        GLFWwindow* _window;

        GrDirectContext* _context = nullptr;
        GrGLFramebufferInfo _frameBuffer;
        GrBackendRenderTarget _renderTarget;
        SkSurface* _surface = nullptr;

        public:
            DrawWindow(class snuifw::Context*);

            ~DrawWindow();

        public:
            virtual IDrawContext* drawContext() override { return nullptr; }

        public:
            // TODO take reference to window? can force make current behaviour with that
            void prepareContext(int width, int height);
            bool rebuildSurface(int width, int height);
    };
}
