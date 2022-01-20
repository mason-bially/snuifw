
#pragma once
#include "common.h"
#include "snuifw.h"

// TODO remove these references
#include "snuifw/draw/skia.h"

namespace snuifw
{
    // TODO put this somewhere else
    class ModelStore
    {
        static size_t _s_typeid;

        std::unordered_map<size_t, void*> _erased_store;

    public:
        template<typename TModel>
        static inline size_t asStoreId()
        {
            static size_t _typeid = _s_typeid++;
            return _typeid;
        }

        template<typename TModel>
        inline TModel const* getModel() const
        {
            size_t id = asStoreId<TModel>();

            auto it = _erased_store.find(id);
            if (it == _erased_store.end())
                return nullptr;
            return static_cast<TModel const*>(it->second);
        }

        template<typename TModel, typename Func>
        inline void mutModel(Func func)
        {
            size_t id = asStoreId<TModel>();

            void** model = &_erased_store[id];
            if (*model == nullptr)
                (*model) = static_cast<void*>(new TModel);

            func(static_cast<TModel*>(*model));
        }
    };

    class Context 
    {
    private:
        TopContext* _top;
        ModelStore _model;

        DomRoot _dom;

    // TODO move these implementation details
    private:
        IApplicationWindow::WindowDescription _windowDesc;
        GLFWwindow* _window;
        skia::DrawWindow _draw;
        friend class skia::DrawWindow;

    public:
        Context(TopContext* top);

    public:
        inline ModelStore& model() { return _model; }
        inline ModelStore const& model() const { return _model; }

    public:
        inline DomRoot& dom() { return _dom; }

        inline void setDom(std::shared_ptr<IElement> elem)
        {
            _dom.setRoot(elem);
        }

    public:
        inline SkSurface* getSurface() { return _draw._surface; };
        inline GLFWwindow* getWindow() { return _window; }

    public:
        void setWindowDescription(IApplicationWindow::WindowDescription);

    public:
        void init();
        void teardown();
        bool isRunning();
        void close();

        std::function<void ()> loop; // not rate limited

        void update();

    public:
        void swap(); // is vsync right now

    private:
        void _initGlfw();
        void _initSkia();
        void _fillWindowEvents();

    private:
        void _keyCallback(int k, int s, int a, int m);
        void _charCallback(unsigned int c);
        void _cursorPositionCallback(double x, double y);
        void _windowFocusCallback(int i);
        void _framebufferResizeCallback(int w, int h);
    };
}
