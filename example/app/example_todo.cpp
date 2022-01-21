#include "snuifw/snuifw.h"

#include <map>

using namespace snuifw;

char ipsum[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor"
 " incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation"
 " ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit"
 " in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat"
 " cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

class MyBox
    : public IComponent
{
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
            Box().color(rgb(255, 0, 0)).size(px(100.f, 100.f)),
            Box().color(rgb(255, 64, 0)).size(px(100.f, 100.f))
        ];
    }
};

struct TestModel
{
    int a;
};

static std::map<std::string, snuifw::literal::StyleColor4b> colors = {
    {"Black", hex(0x000000)},
    {"White", hex(0xFFFFFF)},
    {"Gray_50", hex(0xF7FAFC)},
    {"Gray_100", hex(0xEDF2F7)},
    {"Gray_200", hex(0xE2E8F0)},
    {"Gray_300", hex(0xCBD5E0)},
    {"Gray_400", hex(0xA0AEC0)},
    {"Gray_500", hex(0x718096)},
    {"Gray_600", hex(0x4A5568)},
    {"Gray_700", hex(0x2D3748)},
    {"Gray_800", hex(0x1A202C)},
    {"Gray_900", hex(0x171923)},
    {"Red_50", hex(0xFFF5F5)},
    {"Red_100", hex(0xFED7D7)},
    {"Red_200", hex(0xFEB2B2)},
    {"Red_300", hex(0xFC8181)},
    {"Red_400", hex(0xF56565)},
    {"Red_500", hex(0xE53E3E)},
    {"Red_600", hex(0xC53030)},
    {"Red_700", hex(0x9B2C2C)},
    {"Red_800", hex(0x822727)},
    {"Red_900", hex(0x63171B)},
    {"Orange_50", hex(0xFFFAF0)},
    {"Orange_100", hex(0xFEEBC8)},
    {"Orange_200", hex(0xFBD38D)},
    {"Orange_300", hex(0xF6AD55)},
    {"Orange_400", hex(0xED8936)},
    {"Orange_500", hex(0xDD6B20)},
    {"Orange_600", hex(0xC05621)},
    {"Orange_700", hex(0x9C4221)},
    {"Orange_800", hex(0x7B341E)},
    {"Orange_900", hex(0x652B19)},
    {"Yellow_50", hex(0xFFFFF0)},
    {"Yellow_100", hex(0xFEFCBF)},
    {"Yellow_200", hex(0xFAF089)},
    {"Yellow_300", hex(0xF6E05E)},
    {"Yellow_400", hex(0xECC94B)},
    {"Yellow_500", hex(0xD69E2E)},
    {"Yellow_600", hex(0xB7791F)},
    {"Yellow_700", hex(0x975A16)},
    {"Yellow_800", hex(0x744210)},
    {"Yellow_900", hex(0x5F370E)},
    {"Green_50", hex(0xF0FFF4)},
    {"Green_100", hex(0xC6F6D5)},
    {"Green_200", hex(0x9AE6B4)},
    {"Green_300", hex(0x68D391)},
    {"Green_400", hex(0x48BB78)},
    {"Green_500", hex(0x38A169)},
    {"Green_600", hex(0x2F855A)},
    {"Green_700", hex(0x276749)},
    {"Green_800", hex(0x22543D)},
    {"Green_900", hex(0x1C4532)},
    {"Teal_50", hex(0xE6FFFA)},
    {"Teal_100", hex(0xB2F5EA)},
    {"Teal_200", hex(0x81E6D9)},
    {"Teal_300", hex(0x4FD1C5)},
    {"Teal_400", hex(0x38B2AC)},
    {"Teal_500", hex(0x319795)},
    {"Teal_600", hex(0x2C7A7B)},
    {"Teal_700", hex(0x285E61)},
    {"Teal_800", hex(0x234E52)},
    {"Teal_900", hex(0x1D4044)},
    {"Blue_50", hex(0xEBF8FF)},
    {"Blue_100", hex(0xBEE3F8)},
    {"Blue_200", hex(0x90CDF4)},
    {"Blue_300", hex(0x63B3ED)},
    {"Blue_400", hex(0x4299E1)},
    {"Blue_500", hex(0x3182CE)},
    {"Blue_600", hex(0x2B6CB0)},
    {"Blue_700", hex(0x2C5282)},
    {"Blue_800", hex(0x2A4365)},
    {"Blue_900", hex(0x1A365D)},
    {"Cyan_50", hex(0xEDFDFD)},
    {"Cyan_100", hex(0xC4F1F9)},
    {"Cyan_200", hex(0x9DECF9)},
    {"Cyan_300", hex(0x76E4F7)},
    {"Cyan_400", hex(0x0BC5EA)},
    {"Cyan_500", hex(0x00B5D8)},
    {"Cyan_600", hex(0x00A3C4)},
    {"Cyan_700", hex(0x0987A0)},
    {"Cyan_800", hex(0x086F83)},
    {"Cyan_900", hex(0x065666)},
    {"Purple_50", hex(0xFAF5FF)},
    {"Purple_100", hex(0xE9D8FD)},
    {"Purple_200", hex(0xD6BCFA)},
    {"Purple_300", hex(0xB794F4)},
    {"Purple_400", hex(0x9F7AEA)},
    {"Purple_500", hex(0x805AD5)},
    {"Purple_600", hex(0x6B46C1)},
    {"Purple_700", hex(0x553C9A)},
    {"Purple_800", hex(0x44337A)},
    {"Purple_900", hex(0x322659)},
    {"Pink_50", hex(0xFFF5F7)},
    {"Pink_100", hex(0xFED7E2)},
    {"Pink_200", hex(0xFBB6CE)},
    {"Pink_300", hex(0xF687B3)},
    {"Pink_400", hex(0xED64A6)},
    {"Pink_500", hex(0xD53F8C)},
    {"Pink_600", hex(0xB83280)},
    {"Pink_700", hex(0x97266D)},
    {"Pink_800", hex(0x702459)},
    {"Pink_900", hex(0x521B41)},
};



int main(void) {
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
            
            Box().color(colors["Gray_100"]).size(px(640, 80)),
            Text().font(sans_font).value("TODOs"),
            Box().color(colors["Gray_200"]).size(px(640, 400))
        ]
    );
    c->init();



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