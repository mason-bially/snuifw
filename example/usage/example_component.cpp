#include "snuifw/snuifw.h"

using namespace snuifw;

char ipsum[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor"
 " incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation"
 " ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit"
 " in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat"
 " cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

class MyBox
    : public IComponent
{
    SkColor _color;
    SkSize _size;
    
    void _dirtyLayout();

public:
    inline MyBox() = default;
    inline virtual ~MyBox() = default;

    operator std::shared_ptr<IElement>() const { return std::static_pointer_cast<IElement>(std::make_shared<MyBox>(*this)); }

protected:
    virtual bool propsChanged() const override
    {
        return false;
    }
    virtual std::shared_ptr<IElement> render() override
    {
        return VFlow().stretch(false) [
            Box().color(SkColorSetARGB(255, 255, 0, 0)).size(px(100.f, 100.f)),
            Box().color(SkColorSetARGB(255, 255, 64, 0)).size(px(100.f, 100.f))
        ];
    }
};

int main(void) {
    Context c;
    c.init();

    // TODO, make a manager
    auto default_font = SkFont(SkTypeface::MakeDefault(), 20);
    auto sans_font = SkFont(SkTypeface::MakeFromName("DejaVu Sans", SkFontStyle::Normal()), 10);
    auto mono_font = SkFont(SkTypeface::MakeFromName("DejaVu Sans Mono", SkFontStyle::Normal()), 10);

    auto fancy_font = default_font;
    fancy_font.setSubpixel(true);
    fancy_font.setHinting(SkFontHinting::kFull);
    fancy_font.setForceAutoHinting(true);
    fancy_font.setEdging(SkFont::Edging::kSubpixelAntiAlias);

    auto dom = new DomRoot(&c);
    dom->setRoot(
        VFlow().flow(false).stretch(false) [
            Box().color(SkColorSetARGB(255, 255, 0, 255)).size(px(20.f, 20.f)),
            Text().value(std::to_string(__cplusplus)).font(default_font),
            Text().value(ipsum).font(default_font),
            Text().value(ipsum).font(fancy_font),
            Text().value(ipsum).font(sans_font).spacing_add(-2.f),
            Text().value(ipsum).font(mono_font).spacing_mul(1.2),
            MyBox()
        ]);

	c.loop = [&]()
    {
		dom->render();

        c.swap();
    };

    c.main();

	exit(EXIT_SUCCESS);
}