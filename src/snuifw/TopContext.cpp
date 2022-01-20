#include "TopContext.h"
#include "snuifw/snuifw.h"

using namespace snuifw;

void TopContext::init()
{
    _initGlfw();
    _initSkia();
}

void TopContext::teardown()
{
    for (auto context : _contexts)
    {
        context->teardown();
        delete context;
    }

    glfwTerminate();
}

bool TopContext::isRunning()
{
    return !_canceled && _contexts.size() != 0;
}

void TopContext::shutdown()
{
    _canceled = true;
    
    for (auto context : _contexts)
    {
        context->close();
    }
}

void TopContext::main()
{
    _canceled = false;
    _inMain = true;
    while (isRunning())
    {
        update_all();
    }
    _inMain = false;
}

void TopContext::update_all()
{
    glfwWaitEvents();

    if (loop)
        loop();

    std::list<Context*> remove_list;
    for (auto context : _contexts)
    {
        context->update();
        if (!context->isRunning())
            remove_list.push_back(context);
    }

    for (auto context : remove_list)
    {
        context->teardown();
        _contexts.erase(std::find(_contexts.begin(), _contexts.end(), context));
        delete context;
    }
}


void TopContext::_initGlfw()
{
    if (!glfwInit()) {
        throw std::runtime_error("GLFW Problem Bro");
    }
}

void TopContext::_initSkia()
{
}
