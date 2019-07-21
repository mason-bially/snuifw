#include "simple.h"

using namespace snuifw;

void Box::_dirtyLayout()
{
    _layout.minHeight = _layout.prefHeight = _size.height();
    _layout.minWidth = _layout.prefWidth = _size.width();
}

void Box::draw(SkCanvas* canvas)
{
    canvas->drawColor(_color);
}
