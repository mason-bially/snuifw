#pragma once
#include "snuifw/common.h"
#include "snuifw/dom/dom.h"

namespace snuifw {
    class VTile
        : public IFundamental
        , private FlowLayouter<true>
    {
    private:
        LayoutDescription _layout;

        std::vector<std::shared_ptr<IElement>> _children;

    public:
        VTile();
        inline virtual ~VTile() = default;

        operator std::shared_ptr<IElement>() const { return std::static_pointer_cast<IElement>(std::make_shared<VTile>(*this)); }

    public:
        inline VTile& operator[](std::vector<std::shared_ptr<IElement>> children) { _children = children; return *this; }
        inline VTile& operator[](std::shared_ptr<IElement> child) { _children = { child }; return *this; }

    protected:
        inline virtual std::vector<std::shared_ptr<IElement>> const* children() { return &_children; }

    protected:
        inline virtual LayoutDescription layoutDescription() const override { return _layout; }
        inline virtual ILayoutCalculator* layoutCalculator() const override { return (FlowLayouter<true>*)this; }
        virtual void draw(SkCanvas* canvas) override;
    };
}
