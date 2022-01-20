#include "snuifw/snuifw.h"

using namespace snuifw;

char ipsum[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor"
 " incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation"
 " ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit"
 " in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat"
 " cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

int main(void) {
    TopContext top;
    top.init();

    // TODO, make a manager
    auto default_font = SkFont(SkTypeface::MakeDefault(), 20);
    auto sans_font = SkFont(SkTypeface::MakeFromName("DejaVu Sans", SkFontStyle::Normal()), 10);
    auto mono_font = SkFont(SkTypeface::MakeFromName("DejaVu Sans Mono", SkFontStyle::Normal()), 10);

    auto fancy_font = default_font;
    fancy_font.setSubpixel(true);
    fancy_font.setHinting(SkFontHinting::kFull);
    fancy_font.setForceAutoHinting(true);
    fancy_font.setEdging(SkFont::Edging::kSubpixelAntiAlias);

    auto c = new Context(&top);
    c->setDom(
        VFlow().flow(false).stretch(false) [
            Box().color(rgb(255, 0, 255)).size(px(20.f, 20.f)),
            Text().value(std::to_string(__cplusplus)).font(default_font),
            Text().value(ipsum).font(default_font),
            Text().value(ipsum).font(fancy_font),
            Text().value(ipsum).font(sans_font).spacing_add(-2.f),
            Text().value(ipsum).font(mono_font).spacing_mul(1.2),
            VFlow().stretch(false) [
                Box().color(rgb(255, 0, 0)).size(px(100, 100)),
                Box().color(rgb(255, 64, 0)).size(px(100, 100)),
                Box().color(rgb(255, 128, 0)).size(px(100, 200)),
                Box().color(rgb(255, 64, 0)).size(px(100, 100)),
                Box().color(rgb(255, 0, 0)).size(px(100, 100)),
                Box().color(rgb(255, 0, 0)).size(px(100, 100)),
                Box().color(rgb(255, 64, 0)).size(px(100, 100)),
                Box().color(rgb(255, 128, 0)).size(px(100.f, 200.f)),
                Box().color(rgb(255, 64, 0)).size(px(100.f, 100)),
                Box().color(rgb(255, 0, 0)).size(px(100, 100.f))
            ]
        ]);
    c->init();
    
    top.main();

	exit(EXIT_SUCCESS);
}
