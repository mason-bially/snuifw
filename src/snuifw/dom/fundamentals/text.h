#pragma once
#include "snuifw/common.h"
#include "snuifw/dom/dom.h"

namespace snuifw {
    class Text
        : public IFundamental
    {
        LayoutDescription _layout;

        std::string _s;
        
        void _dirtyLayout();

    public:
        inline Text() = default;
        inline virtual ~Text() = default;

        operator std::shared_ptr<IElement>() const { return std::static_pointer_cast<IElement>(std::make_shared<Text>(*this)); }

    public:
        inline Text& value(std::string const& s) {  _s = s; _dirtyLayout(); return *this; }

    protected:
        inline virtual LayoutDescription layoutDescription() const override { return _layout; }
        virtual void layoutBounds(SkRect* bounds, bool preferWidth) const override;

        virtual void draw(SkCanvas* canvas) override;
    };
}
