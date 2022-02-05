#include "snuifw/snuifw.h"

#include <map>
#include <iostream>

using namespace snuifw;

char ipsum[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor"
 " incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation"
 " ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit"
 " in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat"
 " cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

class Button
    : public IComponent
{
public:
    inline Button() = default;
    inline virtual ~Button() = default;

    operator std::shared_ptr<IElement>() const { return std::static_pointer_cast<IElement>(std::make_shared<Button>(*this)); }

protected:
    virtual bool propsChanged() const override
    {
        return false;
    }
    virtual std::shared_ptr<IElement> render() override
    {
        return VFlow() [
            Box().color(rgb(255, 0, 0)).size(px(100.f, 100.f)),
            Box().color(rgb(255, 64, 0)).size(px(100.f, 100.f))
        ];
    }
};

struct TestModel
{
    int a;
};


int main(void)
{
    TopContext top;
    top.init();

    // TODO, make a manager
    auto default_font = SkFont(SkTypeface::MakeDefault(), 20);
    auto sans_font = SkFont(SkTypeface::MakeFromName("DejaVu Sans", SkFontStyle::Normal()), 32);
    auto mono_font = SkFont(SkTypeface::MakeFromName("DejaVu Sans Mono", SkFontStyle::Normal()), 10);

    auto fancy_font = default_font;
    fancy_font.setSubpixel(true);
    fancy_font.setHinting(SkFontHinting::kFull);
    fancy_font.setForceAutoHinting(true);
    fancy_font.setEdging(SkFont::Edging::kSubpixelAntiAlias);

    auto c = new Context(&top);
    c->setDom(
        VFlow().flow(false).stretch(false) [
            Button()
        ]
    );
    c->init();

    std::cout << snuifw::type::name<IFundamental>() << std::endl;
    std::cout << snuifw::type::name<util::Type>() << std::endl;
    std::cout << snuifw::type::name<TestModel>() << std::endl;
    std::cout << snuifw::type::id<IFundamental>().value << std::endl;
    std::cout << snuifw::type::id<TestModel>().value << std::endl;

    TestModel const* tm = c->model().getModel<TestModel>();
    assert(tm == nullptr);
    c->model().mutModel<TestModel>([](auto tm) {
        tm->a = 15;
    });
    tm = c->model().getModel<TestModel>();
    assert(tm != nullptr);
    assert(tm->a == 15);
    c->model().mutModel<TestModel>([](auto tm) {
        tm->a += 18;
    });
    tm = c->model().getModel<TestModel>();
    assert(tm != nullptr);
    assert(tm->a == (15 + 18));


    top.main();

	exit(EXIT_SUCCESS);
}