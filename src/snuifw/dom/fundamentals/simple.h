#pragma once
#include "snuifw/common.h"
#include "snuifw/dom/dom.h"

namespace snuifw {
    class Box
        : public IFundamental
    {
        LayoutDescription _layout;

        SkColor _color;
        SkSize _size;
        
        void _dirtyLayout();

    public:
        inline Box() = default;
        inline virtual ~Box() = default;

        operator std::shared_ptr<IElement>() const { return std::static_pointer_cast<IElement>(std::make_shared<Box>(*this)); }

    public:
        inline Box& color(SkColor const& color) {  _color = color;  return *this; }
        inline Box& size(SkSize const& size) {  _size = size; _dirtyLayout(); return *this; }

    protected:
        inline virtual LayoutDescription layoutDescription() const override { return _layout; }

        virtual void draw(SkCanvas* canvas) override;
    };
}
