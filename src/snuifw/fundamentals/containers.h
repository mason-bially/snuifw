#pragma once
#include "snuifw/common.h"

#include "snuifw/dom.h"

namespace snuifw {
    class VTile
        : public IFundamental
    {
    private:
        std::vector<std::shared_ptr<IElement>> _children;

    public:
        VTile() = default;
        inline virtual ~VTile() = default;

        operator std::shared_ptr<IElement>() const { return std::static_pointer_cast<IElement>(std::make_shared<VTile>(*this)); }

    public:
        inline VTile& operator[](std::vector<std::shared_ptr<IElement>> children) { _children = children; return *this; }
        inline VTile& operator[](std::shared_ptr<IElement> child) { _children = { child }; return *this; }

    protected:
        inline virtual std::vector<std::shared_ptr<IElement>> const* children() { return &_children; }

    protected:
        virtual SkRect layout(SkRect const& container_bounds) const override;
        virtual void draw(SkCanvas* canvas) override;
    };
}
