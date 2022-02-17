#pragma once
#include "snuifw/common.h"
#include "snuifw/dom/dom.h"

namespace snuifw {
    namespace _details
    {
        template <bool IsVertical>
        class Flow
            : public IElement
            , public IDrawableElement
            , private FlowLayouter<IsVertical>
        {
        private:
            LayoutDescription _layout;

            std::vector<std::shared_ptr<IElement>> _children;

        public:
            Flow();
            inline virtual ~Flow() = default;
            inline virtual util::Type type() const { return type::id<Flow>(); }
            inline virtual ILayoutProviderElement* layoutProviderElement() { return this; }
            inline virtual IDrawableElement* drawableElement() { return this; }

            operator std::shared_ptr<IElement>() const { return std::static_pointer_cast<IElement>(std::make_shared<Flow>(*this)); }

        public:
            inline Flow& operator[](std::vector<std::shared_ptr<IElement>> children) { _children = children; return *this; }
            inline Flow& operator[](std::shared_ptr<IElement> child) { _children = { child }; return *this; }

            inline Flow& flow(bool flow = true) { this->_flowMode = flow; return *this; }
            inline Flow& stretch(bool stretch = true) { this->_stretchMode = stretch; return *this; }

        protected:
            inline virtual std::vector<std::shared_ptr<IElement>> const* children() const override { return &_children; }

        protected:
            virtual void draw(DrawContext& ctx, LayoutResult const& layout) const override;
        };
    }

    using VFlow = _details::Flow<true>;
    using HFlow = _details::Flow<false>;
}
