#include "text.h"

using namespace snuifw;

void Text::_dirtyLayout()
{
    SkFont font;
    SkRect res;
    font.measureText(_s.c_str(), _s.size(), SkTextEncoding::kUTF8, &res);

    _layout.prefWidth = res.width();
    _layout.prefHeight = res.height();

    _layout.flags = LayoutDescription::HasHeightCalculator;
}

void Text::layoutBounds(SkRect* bounds, bool preferWidth = true) const
{
    // TODO break paragraphs
    bounds->fBottom = std::min(bounds->fBottom, bounds->fTop + _layout.prefHeight);
}

void Text::draw(SkCanvas* canvas)
{
    SkFont font;
    SkPaint paint;
    paint.setAntiAlias(true);

    canvas->drawSimpleText(_s.c_str(), _s.size(), SkTextEncoding::kUTF8, 0, 12, font, paint);
}
