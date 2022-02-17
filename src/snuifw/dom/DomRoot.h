#pragma once
#include "snuifw/common.h"
#include "snuifw/dom/dom.h"

namespace snuifw {

    class DomRoot
    {
    private:
        struct ShadowDom
        {
            // The resolution stack for this element
            std::deque<std::shared_ptr<IElement>> shadowStack;
            
            // The actual children of this element
            std::vector<ShadowDom> shadowChildren;

            // All bounds stored local to parent
            ScreenRect bounds;

            std::shared_ptr<IDrawableElement> drawable;
            std::shared_ptr<IInteractableElement> interactable;
        };

    private:
        class Context* _context;
        std::shared_ptr<IElement> _rootElement;

        ShadowDom _shadow;

    private:
        void _shadowRender(ShadowDom& shadow, std::shared_ptr<IElement> const& elem);
        void _shadowLayout(ShadowDom& shadow, SkRect* bounds);
        void _shadowDraw(SkCanvas* canvas, ShadowDom const& d);

    public:
        DomRoot(Context* context);

        std::shared_ptr<IElement> getRoot();
        void setRoot(std::shared_ptr<IElement>);

        void render();
    };
}
