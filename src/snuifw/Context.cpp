#include "Context.h"

using namespace snuifw;

size_t ModelStore::_s_typeid = 1;

Context::Context(TopContext* top)
    : _top(top)
    , _model()
    , _dom(this)
    , _windowDesc(), _window(nullptr)
    , _draw(this)
{
    // TODO make thread safe against top
    _top->_contexts.push_back(this);
}

void Context::setWindowDescription(IApplicationWindow::WindowDescription desc)
{
    _windowDesc = desc;
}

void Context::init()
{
    _initGlfw();
    _initSkia();
}

void Context::teardown()
{
    
}

bool Context::isRunning()
{
    return !glfwWindowShouldClose(_window);
}

void Context::close()
{
    glfwSetWindowShouldClose(_window, true);
}

void Context::swap()
{
	glfwSwapBuffers(_window);
}

void Context::update()
{
    if (loop)
        loop();

    _dom.render();
    swap();
}

void Context::_initGlfw()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //(uncomment to enable correct color spaces) glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
    glfwWindowHint(GLFW_STENCIL_BITS, 0);
    //glfwWindowHint(GLFW_ALPHA_BITS, 0);
    glfwWindowHint(GLFW_DEPTH_BITS, 0);

    _window = glfwCreateWindow(_windowDesc.width, _windowDesc.height, _windowDesc.title.c_str(), NULL, NULL);
    if (!_window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(_window);
    glfwSetWindowUserPointer(_window, this);		
    glfwSwapInterval(1);

    _fillWindowEvents();
}

void Context::_initSkia()
{
    _draw.prepareContext(_windowDesc.width, _windowDesc.height);
}

void Context::_fillWindowEvents()
{
    glfwSetKeyCallback(_window,
        [](GLFWwindow* w, int k, int s, int a, int m)
        {
            static_cast<Context*>(glfwGetWindowUserPointer(w))->_keyCallback(k, s, a, m);
        });
    glfwSetCharCallback(_window,
        [](GLFWwindow* w, unsigned int c)
        {
            static_cast<Context*>(glfwGetWindowUserPointer(w))->_charCallback(c);
        });
    glfwSetWindowFocusCallback(_window,
        [](GLFWwindow* w, int i)
        {
            static_cast<Context*>(glfwGetWindowUserPointer(w))->_windowFocusCallback(i);
        });
    glfwSetFramebufferSizeCallback(_window,
        [](GLFWwindow* w, int d, int h)
        {
            static_cast<Context*>(glfwGetWindowUserPointer(w))->_framebufferResizeCallback(d, h);
        });
}

void Context::_keyCallback(int k, int s, int a, int m)
{

}

void Context::_charCallback(unsigned int c)
{

}

void Context::_windowFocusCallback(int i) 
{

}


void Context::_framebufferResizeCallback(int w, int h)
{
    // TODO, decompose these events to be:
    // - NativeWindowResized
    //   - _rebuildSurface
    //   - AppWindowResized
    _draw.rebuildSurface(w, h);
    _dom.render();
    swap();
}
