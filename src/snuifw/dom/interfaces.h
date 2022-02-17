#pragma once
#include "snuifw/common.h"
#include "snuifw/dom/dom.h"

namespace snuifw
{
    struct LayoutContext
    {
        util::Type type;
        void* ctx;

        template<typename T> bool is() { return type.value != 0 && type::id<T>() == type.value; }
        template<typename T> T* as() { assert(is<T>()); return reinterpret_cast<T*>(ctx); }
    };

    struct LayoutResult
    {
        util::Type type;
        void const* result;
        ScreenRect rect;
    };

    struct DrawContext
    {
        util::Type type;
        void* ctx;

        template<typename T> bool is() { return type.value != 0 && type::id<T>() == type.value; }
        template<typename T> T* as() { assert(is<T>()); return reinterpret_cast<T*>(ctx); }
    };

    struct InteractContext
    {
        util::Type type;
        void* ctx;

        template<typename T> bool is() { return type.value != 0 && type::id<T>() == type.value; }
        template<typename T> T* as() { assert(is<T>()); return reinterpret_cast<T*>(ctx); }
    };


    class ILayoutElement;
    class ILayoutProviderElement;
    class IDrawableElement;
    class IInteractableElement;
    class IElement;
    class IComponent;


    class ILayoutProviderElement
    {
    public:
        static util::DeclareType<ILayoutProviderElement> s_type;
        static constexpr char const c_cppTypeName[] = "snuifw::ILayoutProviderElement";

    public:
        virtual ~ILayoutProviderElement();
        virtual util::Type type() const = 0;

    public:
        // Provides the layout for the given children
        virtual void provideLayout(LayoutContext& ctx, LayoutResult const& layout, std::vector<std::shared_ptr<IElement>> const& children,  std::vector<LayoutResult> & results) = 0;
    };


    class ILayoutElement
    {
    public:
        static util::DeclareType<ILayoutElement> s_type;
        static constexpr char const c_cppTypeName[] = "snuifw::ILayoutElement";

    public:
        virtual ~ILayoutElement();
        virtual util::Type type() const = 0;

    public:
        virtual void layout(LayoutContext& ctx, LayoutResult& layout) const = 0;
    };


    class IDrawableElement
    {
    public:
        static util::DeclareType<IDrawableElement> s_type;
        static constexpr char const c_cppTypeName[] = "snuifw::IDrawableElement";

    public:
        inline virtual ~IDrawableElement();
        virtual util::Type type() const = 0;

    public:
        virtual void draw(DrawContext& ctx, LayoutResult const& layout) const = 0;

        // TODO, some sort of strategy+memoization pattern for speedup
    };


    class IInteractableElement
    {
    public:
        static util::DeclareType<IInteractableElement> s_type;
        static constexpr char const c_cppTypeName[] = "snuifw::IInteractableElement";

    public:
        inline virtual ~IInteractableElement();
        virtual util::Type type() const = 0;

    public:
        virtual void interact(InteractContext& ctx) = 0;
    };


    class IElement 
    {
    public:
        static util::DeclareType<IElement> s_type;
        static constexpr char const c_cppTypeName[] = "snuifw::IElement";

    public:
        virtual ~IElement();
        virtual util::Type type() const = 0;

    public:
        virtual ILayoutProviderElement* layoutProviderElement();
        virtual ILayoutElement* layoutElement();
        virtual IDrawableElement* drawableElement();
        virtual IInteractableElement* interactableElement();
        virtual IComponent* component();

        virtual std::vector<std::shared_ptr<IElement>> const* children() const;
    };



    class IComponent
        : public IElement
    {
    public:
        static util::DeclareType<IComponent> s_type;
        static constexpr char const c_cppTypeName[] = "snuifw::IComponent";

    public:
        virtual ~IComponent();

    public:
        virtual bool propsChanged() const = 0;
        virtual std::shared_ptr<IElement> render() = 0;
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
