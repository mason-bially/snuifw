#pragma once
#include "snuifw/common.h"

#include "snuifw/context.h"

namespace snuifw {

    class DomRoot
    {
    private:
        struct ShadowDom
        {
            // Take the 0'th element to get the fundamental
            std::deque<std::shared_ptr<IElement>> shadowStack;
            
            std::vector<ShadowDom> shadowChildren;

            // All bounds stored local to parent
            SkRect bounds;

            inline std::shared_ptr<IElement> const& front() const
            {
                return shadowStack.front();
            }

            inline std::shared_ptr<IFundamental> getFundamental() const
            {
                return std::static_pointer_cast<IFundamental>(shadowStack.front());
            }
        };

    private:
        Context* _context;
        std::shared_ptr<IElement> _root;

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
