#pragma once
#include "snuifw/common.h"
#include "snuifw/dom/dom.h"

namespace snuifw {
    /* This is a flowing piece of text, it is simple, and nothing more.
     */
    class Text
        : public IFundamental
    {
        mutable LayoutDescription _layout;

        // TODO text theming manager to cache these, via a flyweight
        mutable float _fontHeight;
        mutable float _fontRenderHeight;
        mutable float _scaledSpacing;

        std::string _value;
        SkFont const* _font = nullptr;
        float _spaceAdd = 0.f;
        float _spaceMul = 1.f;
        
        // TODO ensure _reflowText gets called if the layout is dirty.
        struct Line
        {
            std::string_view value;
            float width;
        };
        mutable std::vector<Line> _lines;
        mutable float _longestLine;
        mutable std::string_view _unflowed;
        float _calcLinesHeight() const;

        mutable bool _dirtyLayout = true;
        void _recomputeLayout(SkRect* reflow_bounds = nullptr) const;
        void _reflowText(SkRect const& bounds) const;

    public:
        inline Text() = default;
        inline virtual ~Text() = default;

        operator std::shared_ptr<IElement>() const { return std::static_pointer_cast<IElement>(std::make_shared<Text>(*this)); }

    public:
        inline Text& value(std::string const& s) {  _value = s; _dirtyLayout = true; return *this; }
        inline Text& font(SkFont const& f) {  _font = &f; _dirtyLayout = true; return *this; }
        inline Text& spacing_add(float space = 0.f) {  _spaceAdd = space; _dirtyLayout = true; return *this; }
        inline Text& spacing_mul(float space = 1.f) {  _spaceMul = space; _dirtyLayout = true; return *this; }

    protected:
        inline virtual LayoutDescription const& layoutDescription() const override { _recomputeLayout(); return _layout; }
        virtual void layoutBounds(SkRect* bounds, bool preferWidth) const override;

        virtual void draw(SkCanvas* canvas) override;
    };
}
