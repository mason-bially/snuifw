#include "snuifw/snuifw.h"
#include "snuifw/draw/skia/internal.h"

#include "simple.h"

using namespace snuifw;

void Box::_dirtyLayout()
{
    _layout.minHeight = _layout.prefHeight = _size.getYf();
    _layout.minWidth = _layout.prefWidth = _size.getXf();
}

void Box::draw(DrawContext& ctx, LayoutResult const& layout) const
{
    if (ctx.is<SkCanvas>())
    {
        auto canvas = ctx.as<SkCanvas>();
        canvas->drawColor(_color.asUint(StyleColor4b::Flags::BGRA));

        return;
    }

    throw std::runtime_error("not implemented draw context type"); // TODO snuifw::error::not_implemented_context_type
}

void Box::layout(LayoutContext& ctx, LayoutResult& layout) const
{
    layout.result = &_layout;
    layout.type = type::id<LayoutDescription>();
}
