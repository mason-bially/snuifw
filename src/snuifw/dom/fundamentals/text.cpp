#include "text.h"

using namespace snuifw;

float Text::_calcLinesHeight() const
{
    return _lines.size() * _scaledSpacing;
}

void Text::_recomputeLayout(SkRect* reflow_bounds) const
{
    if (!_dirtyLayout)
    {
        if (reflow_bounds != nullptr)
            _reflowText(*reflow_bounds);
        
        return;
    }
    
    _lines.clear();
    _unflowed = std::string_view();

    SkFont const& font = _font == nullptr ? SkFont() : *_font;

    SkFontMetrics fontMetrics;
    _fontHeight = font.getMetrics(&fontMetrics);
    _fontRenderHeight = fontMetrics.fAscent;
    _scaledSpacing = _fontHeight * _spaceMul + _spaceAdd;

    SkRect res;
    auto width = font.measureText(_value.c_str(), _value.size(), SkTextEncoding::kUTF8);

    if (_layout.prefWidth != width || _layout.prefHeight != _scaledSpacing)
    {
        _layout.prefWidth = width;
        _layout.prefHeight = _scaledSpacing;

        _layout.flags = LayoutDescription::HasHeightCalculator;

        if (reflow_bounds != nullptr)
            _reflowText(*reflow_bounds);
    }

    _dirtyLayout = false;
}

void Text::_reflowText(SkRect const& bounds) const
{
    _lines.clear();
    _longestLine = 0.f;

    SkFont const& font = _font == nullptr ? SkFont() : *_font;
    size_t end = _value.size(), line_begin = 0, last_break = 0, i = 0;
    bool seen_content = false;
    float last_measure = 0.f;

    bool over_flowed = false;

    while (i < end)
    {
        bool action_break = false;

        auto const& v = _value[i];
        if (v == ' ')
        {
            seen_content = true;
            auto potential_measure = font.measureText(&_value[line_begin], i - line_begin, SkTextEncoding::kUTF8);

            if (potential_measure > bounds.width())
                action_break = true;
            else
            {
                last_measure = potential_measure;
                last_break = i;
                i += 1;
            }
        }
        else if (v == '\n' || v == '\r')
        {
            action_break = seen_content;
            i += 1;
        }
        else
        {
            seen_content = true;
            i += 1;
        }

        if (action_break)
        {
            _lines.push_back({ std::string_view(&_value[line_begin], last_break - line_begin), last_measure });
            line_begin = last_break + 1;
            seen_content = false;
            _longestLine = std::max(_longestLine, last_measure);
            last_measure = 0.f;

            if (_calcLinesHeight() > bounds.height())
            {
                over_flowed = true;
                break;
            }
        }
    }

    if (!over_flowed)
    {
        last_measure = font.measureText(&_value[line_begin], end - line_begin, SkTextEncoding::kUTF8);
        _longestLine = std::max(_longestLine, last_measure);
        _lines.push_back({ std::string_view(&_value[line_begin], end - line_begin), last_measure });
    }
    else
    {
        _unflowed = std::string_view(&_value[i], end - i);
    }
}

void Text::layoutBounds(SkRect* bounds, bool preferWidth = true) const
{
    _recomputeLayout(bounds);

    bounds->fBottom = std::min(bounds->fBottom, bounds->fTop + _calcLinesHeight());
}

void Text::draw(SkCanvas* canvas)
{
    SkPaint paint;
    paint.setAntiAlias(true);

    SkFont const& font = _font == nullptr ? SkFont() : *_font;

    auto y = -_fontRenderHeight;
    for (auto line : _lines)
    {
        canvas->drawSimpleText(line.value.data(), line.value.size(), SkTextEncoding::kUTF8, 0, y, font, paint);
        y += _scaledSpacing;
    }
}
