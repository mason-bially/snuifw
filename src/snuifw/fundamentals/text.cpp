#include "text.h"

using namespace snuifw;

SkRect Text::layout(SkRect const& container_bounds) const
{
    SkFont font;
    SkRect res;
    font.measureText(_s.c_str(), _s.size(), SkTextEncoding::kUTF8, &res);
    //TODO Paragraph
    return res;
}

void Text::draw(SkCanvas* canvas)
{
    SkFont font;
    SkPaint paint;
    paint.setAntiAlias(true);

    canvas->drawSimpleText(_s.c_str(), _s.size(), SkTextEncoding::kUTF8, 0, 0, font, paint);
}