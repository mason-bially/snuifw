#pragma once
#include "snuifw/common.h"

#include "snuifw/dom.h"

namespace snuifw {
    class Text
        : public IFundamental
    {
        std::string _s;
    public:
        inline Text() = default;
        inline virtual ~Text() = default;

        operator std::shared_ptr<IElement>() const { return std::static_pointer_cast<IElement>(std::make_shared<Text>(*this)); }

    public:
        inline Text& value(std::string const& s) { _s = s; return *this; }

    protected:
        virtual SkRect layout(SkRect const& container_bounds) const override;
        virtual void draw(SkCanvas* canvas) override;
    };
}
