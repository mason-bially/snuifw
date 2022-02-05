#include "simple.h"

using namespace snuifw;

void Box::_dirtyLayout()
{
    _layout.minHeight = _layout.prefHeight = _size.getYf();
    _layout.minWidth = _layout.prefWidth = _size.getXf();
}

void Box::draw(SkCanvas* canvas)
{
    canvas->drawColor(_color.asUint(StyleColor4b::Flags::BGRA));
}
