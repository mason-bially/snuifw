#pragma once
#include "snuifw/common.h"

namespace snuifw {


    class IElement 
    {
    public:
        inline virtual ~IElement() = default;

    public:
        virtual bool isFundamental() = 0;

        inline virtual std::vector<std::shared_ptr<IElement>> const* children() { return nullptr; }
    };

    class IFundamental
        : public IElement
    {
    public:
        inline virtual ~IFundamental() = default;

    public:
        inline virtual bool isFundamental() override { return true; }

    public:
        virtual SkRect layout(SkRect const& container_bounds) const = 0;
        virtual void draw(SkCanvas* canvas) = 0;
    };

    class IComponent
        : public IElement
    {
    public:
        inline virtual ~IComponent() = default;

    public:
        inline virtual bool isFundamental() override { return false; }

    public:
        virtual bool propsChanged() = 0;
        virtual std::unique_ptr<IElement> render() = 0;
    };


    // hacks
    inline std::vector<std::shared_ptr<IElement>> operator,(std::vector<std::shared_ptr<IElement>> a, std::shared_ptr<IElement> b)
    {
        a.push_back(b);
        return a;
    }
    inline std::vector<std::shared_ptr<IElement>> operator,(std::shared_ptr<IElement> a, std::shared_ptr<IElement> b)
    {
        std::vector<std::shared_ptr<IElement>> res;
        res.push_back(a);
        res.push_back(b);
        return res;
    }


    class DomContext
    {
    private:
        struct ShadowDom
        {
            // Take the 0'th element to get the fundamental
            std::deque<std::shared_ptr<IElement>> shadowStack;
            
            std::vector<ShadowDom> shadowChildren;

            SkRect bounds;

            inline std::shared_ptr<IElement> const& front() const
            {
                return shadowStack.front();
            }

            inline std::shared_ptr<IFundamental> getFundamental() const
            {
                return std::static_pointer_cast<IFundamental>(shadowStack.front());
            }
        };

    private:
        SkSurface* _surface;
        std::shared_ptr<IElement> _root;

        ShadowDom _shadow;

    private:
        void _shadowRender(ShadowDom& shadow, std::shared_ptr<IElement> const& elem);
        void _shadowDraw(SkCanvas* canvas, ShadowDom const& d);

    public:
        DomContext(SkSurface* surface);

        std::shared_ptr<IElement> getRoot();
        void setRoot(std::shared_ptr<IElement>);

        void render();
    };
}
