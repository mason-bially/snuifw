#include "glfw.h"
#include "internal.h"

std::unique_ptr<IApplicationLayer> snuifw::glfw::makeApplicationLayer()
{
    return std::make_unique<GlfwApplicationLayer>();
}
