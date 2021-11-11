#include "snuifw/snuifw.h"

int main(int argc, char **argv)
{
    snuifw::Context c;
    c.init();

    c.loop = [&]()
    {

        c.swap();
    };

    c.main();

    return EXIT_SUCCESS;
}
