#pragma once
#include "snuifw/common.h"
#include "snuifw/dom/dom.h"

namespace snuifw {
    // describes the limitations of this component for layout
    struct LayoutDescription
    {
        enum Flags
        {
            // Object can't be sure of bounds until sublayout is done.
            HasLayoutCalculator = 1 << 1,
            // Given the other, can calculate one of these
            HasWidthCalculator = 1 << 2,
            HasHeightCalculator = 1 << 3,
            // Will take as much as it can of each
            UnboundedWidth = 1 << 4,
            UnboundedHeight = 1 << 5,
        };

        Flags flags;

        // If not 0.0, the layouter must do it's best to avoid going under this
        float minWidth;
        float minHeight;

        // If not 0.0, the layouter can assume these are the values it wants
        float prefWidth;
        float prefHeight;

        LayoutDescription()
            : flags((Flags)0)
            , minWidth (0.f), minHeight(0.f)
            , prefWidth (0.f), prefHeight(0.f)
        { }
    };

    class ILayoutEngine
    {
        public:
        // Given the child and the proposed bounds, attempts to get a response
        // The rect should place a 0 where unbounded behaviour can go
        // Otherwise treated as a max size
        // True if bounds are acceptable
        // False if needs to be rebounded (or left in an error state)
        virtual bool attemptChildLayout(size_t child, SkRect* rect, bool preferWidth) = 0;
    };

    template <typename TAttempt>
    class SimpleLayoutEngine final
        : public ILayoutEngine
    {
    private:
        TAttempt _attempter;

    public:
        SimpleLayoutEngine(TAttempt attempter) : _attempter(attempter) {}
        
    protected:
        virtual bool attemptChildLayout(size_t child, SkRect* rect, bool preferWidth) override {
            return _attempter(child, rect, preferWidth);
        }
    };

    class ILayoutCalculator
    {
    public:
        virtual SkRect layout(ILayoutEngine* engine, IFundamental* root, SkRect* agreedBounds, size_t children) const = 0;
    };

    // Code written as if IsVertical is true
    template<bool IsVertical = true>
    class FlowLayouter
        : public ILayoutCalculator
    {
        protected:

        bool _flowMode = true;
        bool _stretchMode = true;

        inline void maybeSwap(SkRect& r) const
        {
            if constexpr (!IsVertical)
            {
                std::swap(r.fLeft, r.fTop);
                std::swap(r.fRight, r.fBottom);
            }
        }

        inline virtual SkRect layout(ILayoutEngine* engine, IFundamental* root, SkRect* agreedBounds_, size_t children) const override
        {
            SkRect agreedBounds = *agreedBounds_;
            maybeSwap(agreedBounds);

            float thisWidth = _stretchMode ? agreedBounds.width() : 0.f;
            float thisHeight = 0.f;
            SkPoint currentLayoutPoint = SkPoint();

            for (decltype(children) i = 0; i < children; ++i)
            {
                SkRect current = SkRect::MakeXYWH(
                    currentLayoutPoint.fX, currentLayoutPoint.fY,
                    agreedBounds.width() - currentLayoutPoint.fX, agreedBounds.height() - currentLayoutPoint.fY);
                maybeSwap(current);

                bool bumpedToNewRow = false;
                if (!_flowMode || !engine->attemptChildLayout(i, &current, IsVertical))
                {
                    // try give it the next part down
                    bumpedToNewRow = true;
                    current = SkRect::MakeXYWH(
                        0.f, thisHeight,
                        agreedBounds.width(), agreedBounds.height() - thisHeight);
                    maybeSwap(current);

                    if (!engine->attemptChildLayout(i, &current, IsVertical))
                        continue;
                }

                maybeSwap(current);
                thisHeight = std::max(current.bottom(), thisHeight);
                if (!_stretchMode)
                    thisWidth = std::max(current.right(), thisWidth);
                currentLayoutPoint.fX = current.right();
                if (bumpedToNewRow)
                    currentLayoutPoint.fY = current.top();
                else if (current.fLeft == agreedBounds.fRight)
                    currentLayoutPoint = SkPoint::Make(0.f, current.top());
            }
            
            SkRect res = SkRect::MakeXYWH(
                0.f, 0.f,
                thisWidth, thisHeight);
            maybeSwap(res);
            return res;
        }
    };
}
