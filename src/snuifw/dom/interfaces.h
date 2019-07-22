#pragma once
#include "snuifw/common.h"
#include "snuifw/dom/dom.h"

namespace snuifw {

    struct LayoutDescription;
    struct ILayoutCalculator;

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
        virtual LayoutDescription const& layoutDescription() const = 0;
        inline virtual ILayoutCalculator const* layoutCalculator() const { return nullptr; }
        virtual void layoutBounds(SkRect* bounds, bool preferWidth = true) const { throw std::runtime_error("Not implemented."); }

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
}