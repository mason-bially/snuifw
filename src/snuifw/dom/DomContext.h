#pragma once
#include "snuifw/common.h"

namespace snuifw {

    class DomContext
    {
    private:
        struct ShadowDom
        {
            // Take the 0'th element to get the fundamental
            std::deque<std::shared_ptr<IElement>> shadowStack;
            
            std::vector<ShadowDom> shadowChildren;

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
        SkSurface* _surface;
        std::shared_ptr<IElement> _root;

        ShadowDom _shadow;

    private:
        void _shadowRender(ShadowDom& shadow, std::shared_ptr<IElement> const& elem);
        void _shadowLayout(ShadowDom& shadow, SkRect* bounds);
        void _shadowDraw(SkCanvas* canvas, ShadowDom const& d);

    public:
        DomContext(SkSurface* surface);

        std::shared_ptr<IElement> getRoot();
        void setRoot(std::shared_ptr<IElement>);

        void render();
    };
}
