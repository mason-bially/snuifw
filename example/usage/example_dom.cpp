#include "GLFW/glfw3.h"

#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "snuifw/snuifw.h"

using namespace snuifw;

//uncomment the two lines below to enable correct color spaces
//#define GL_FRAMEBUFFER_SRGB 0x8DB9
//#define GL_SRGB8_ALPHA8 0x8C43

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

char ipsum[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor"
 " incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation"
 " ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit"
 " in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat"
 " cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

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
            Box().color(SkColorSetARGB(255, 255, 0, 255)).size({ 20.f, 20.f }),
            Text().value(std::to_string(_MSC_VER)).font(default_font),
            Text().value(ipsum).font(default_font),
            Text().value(ipsum).font(fancy_font),
            Text().value(ipsum).font(sans_font).spacing_add(-2.f),
            Text().value(ipsum).font(mono_font).spacing_mul(1.2),
            VFlow().stretch(false) [
                Box().color(SkColorSetARGB(255, 255, 0, 0)).size({ 100.f, 100.f }),
                Box().color(SkColorSetARGB(255, 255, 64, 0)).size({ 100.f, 100.f }),
                Box().color(SkColorSetARGB(255, 255, 128, 0)).size({ 100.f, 200.f }),
                Box().color(SkColorSetARGB(255, 255, 64, 0)).size({ 100.f, 100.f }),
                Box().color(SkColorSetARGB(255, 255, 0, 0)).size({ 100.f, 100.f }),
                Box().color(SkColorSetARGB(255, 255, 0, 0)).size({ 100.f, 100.f }),
                Box().color(SkColorSetARGB(255, 255, 64, 0)).size({ 100.f, 100.f }),
                Box().color(SkColorSetARGB(255, 255, 128, 0)).size({ 100.f, 200.f }),
                Box().color(SkColorSetARGB(255, 255, 64, 0)).size({ 100.f, 100.f }),
                Box().color(SkColorSetARGB(255, 255, 0, 0)).size({ 100.f, 100.f })
            ]
        ]);

	c.loop = [&]()
    {
		dom->render();

        c.swap();
    };

    c.main();

	exit(EXIT_SUCCESS);
}