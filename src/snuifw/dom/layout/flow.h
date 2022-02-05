#pragma once
#include "snuifw/common.h"
#include "snuifw/dom/dom.h"

namespace snuifw {
    namespace _details
    {
        template <bool IsVertical>
        class Flow
            : public IFundamental
            , private FlowLayouter<IsVertical>
        {
        private:
            LayoutDescription _layout;

            std::vector<std::shared_ptr<IElement>> _children;

        public:
            Flow();
            inline virtual ~Flow() = default;

            operator std::shared_ptr<IElement>() const { return std::static_pointer_cast<IElement>(std::make_shared<Flow>(*this)); }

        public:
            inline Flow& operator[](std::vector<std::shared_ptr<IElement>> children) { _children = children; return *this; }
            inline Flow& operator[](std::shared_ptr<IElement> child) { _children = { child }; return *this; }

            inline Flow& flow(bool flow = true) { this->_flowMode = flow; return *this; }
            inline Flow& stretch(bool stretch = true) { this->_stretchMode = stretch; return *this; }

        protected:
            inline virtual std::vector<std::shared_ptr<IElement>> const* children() override { return &_children; }

        protected:
            inline virtual LayoutDescription const& layoutDescription() const override { return _layout; }
            inline virtual ILayoutCalculator* layoutCalculator() const override { return (FlowLayouter<true>*)this; }
            virtual void draw(SkCanvas* canvas) override;
        };
    }

    using VFlow = _details::Flow<true>;
    using HFlow = _details::Flow<false>;
}
