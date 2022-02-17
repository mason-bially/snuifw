#pragma once
#include "snuifw/common.h"
#include "snuifw/literal/literal.h"
#include "snuifw/dom/dom.h"

namespace snuifw {
    class Box
        : public IElement
        , public IDrawableElement
        , public ILayoutElement
    {
    public:
        static util::DeclareType<ILayoutElement> s_type;
        static constexpr char const c_cppTypeName[] = "snuifw::Box";

    private:
        LayoutDescription _layout;

        StyleColor4b _color;
        StyleSize2d _size;
        
        void _dirtyLayout();

    public:
        inline Box() = default;
        inline virtual ~Box() = default;
        inline virtual util::Type type() const { return type::id<Box>(); }
        inline virtual ILayoutElement* layoutElement() { return this; }
        inline virtual IDrawableElement* drawableElement() { return this; }

        operator std::shared_ptr<IElement>() const { return std::static_pointer_cast<IElement>(std::make_shared<Box>(*this)); }

    public:
        inline Box& color(StyleColor4b const& color) {  _color = color;  return *this; }
        inline Box& size(StyleSize2d const& size) {  _size = size; _dirtyLayout(); return *this; }

    protected:
        virtual void layout(LayoutContext& ctx, LayoutResult& layout) const override;

        virtual void draw(DrawContext& ctx, LayoutResult const& layout) const override;
    };
}
