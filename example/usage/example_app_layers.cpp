#include "snuifw/snuifw.h"

int main(int argc, char **argv)
{
    std::unique_ptr<snuifw::IApplicationContext> app_layer;
    std::unique_ptr<snuifw::IDrawContext> draw_layer;

    if (argc >= 1)
    {
        if (std::string("sdl") == argv[0])
            app_layer = snuifw::sdl::makeApplicationLayer();
        else if (std::string("glfw") == argv[0])
            app_layer = snuifw::glfw::makeApplicationLayer();
        else
        {
            std::cout << fmt::format("unknown application layer `{0}`, exiting.", argv[0]);    
            return EXIT_FAILURE;
        }
    }
    else
        app_layer = snuifw::glfw::makeApplicationLayer();


    if (argc >= 2)
    {
        if (std::string("skia") == argv[1])
            draw_layer = snuifw::skia::makeDrawLayer();
        else
        {
            std::cout << fmt::format("unknown draw layer `{0}`, exiting.", argv[1]);    
            return EXIT_FAILURE;
        }
    }
    else
        draw_layer = snuifw::skia::makeDrawLayer();


    snuifw::TopContext top;
    top.setAppLayer(app_layer);
    top.setDrawLayer(draw_layer);
    top.init();

    top.main();

    return EXIT_SUCCESS;
}
