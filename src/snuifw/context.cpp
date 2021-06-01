#include "context.h"

using namespace snuifw;

GLFWwindow * Context::getWindow()
{
	return _model.window.window->window();
}

void Context::init()
{
    _initGlfw();
    _initSkia();
}

void Context::teardown()
{
    dispatch(model::window::a_window {std::make_shared<util::WindowContainer>(nullptr)});
	glfwTerminate();

    delete _surface;
	delete _context;
}

bool Context::isRunning()
{
    return !glfwWindowShouldClose(getWindow()) && !_canceled;
}

void Context::close()
{
	_canceled = true;
}
void Context::main()
{
	_canceled = false;
	_inMain = true;
	while (isRunning())
	{
		glfwWaitEvents();

		loop();
	}
	_inMain = false;
}

void Context::swap()
{
	glfwSwapBuffers(getWindow());
}

void Context::dispatch(model::action a)
{
	_model = model::update(_model, a);
}


void Context::_initGlfw()
{
    if (!glfwInit()) {
		throw std::exception("GLFW Problem Bro");
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//(uncomment to enable correct color spaces) glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
	glfwWindowHint(GLFW_STENCIL_BITS, 0);
	//glfwWindowHint(GLFW_ALPHA_BITS, 0);
	glfwWindowHint(GLFW_DEPTH_BITS, 0);

    auto window = glfwCreateWindow(_model.window.width, _model.window.height, _model.window.name.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);		
    glfwSwapInterval(1);

	dispatch(model::window::a_window {
		std::make_shared<util::WindowContainer>(window)
	});

    _fillWindowEvents();
}

void Context::_initSkia()
{
    GrContextOptions options;
	//options.fRequireDecodeDisableForSRGB = false;
	_context = GrContext::MakeGL(nullptr, options).release();

	_frameBuffer = GrGLFramebufferInfo();
	_renderTarget = GrBackendRenderTarget();

	if (!_rebuildSurface(_model.window.width, _model.window.height))
		throw std::runtime_error("Could not initalize surface.");
}

bool Context::_rebuildSurface(int w, int h)
{
	if (_surface != nullptr)
		delete _surface;

	_frameBuffer.fFBOID = 0; // assume default framebuffer
	// We are always using OpenGL and we use RGBA8 internal format for both RGBA and BGRA configs in OpenGL.
	//(replace line below with this one to enable correct color spaces) framebufferInfo.fFormat = GL_SRGB8_ALPHA8;
	_frameBuffer.fFormat = GL_RGBA8;

	SkColorType colorType;
	if (kRGBA_8888_GrPixelConfig == kSkia8888_GrPixelConfig) {
		colorType = kRGBA_8888_SkColorType;
	}
	else {
		colorType = kBGRA_8888_SkColorType;
	}

	_renderTarget =  GrBackendRenderTarget(
		w, h,
		4, // sample count
		0, // stencil bits
		_frameBuffer);

	//(replace line below with this one to enable correct color spaces) _surface = SkSurface::MakeFromBackendRenderTarget(_context, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, SkColorSpace::MakeSRGB(), nullptr).release();
	_surface = SkSurface::MakeFromBackendRenderTarget(_context, _renderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr).release();
	return _surface != nullptr;
}

void Context::_fillWindowEvents()
{
	#define DREF ((Context*)glfwGetWindowUserPointer(w))
    glfwSetKeyCallback(getWindow(), [](GLFWwindow* w,int k,int s,int a, int m) {DREF->_keyCallback(w, k, s, a, m);});
	glfwSetWindowFocusCallback(getWindow(), [](GLFWwindow* w, int i) {DREF->_windowFocusCallback(w, i);});
	glfwSetFramebufferSizeCallback(getWindow(), [](GLFWwindow* w, int d, int h) {DREF->_framebufferResizeCallback(w, d, h);});
	#undef DREF
}

void Context::_keyCallback(GLFWwindow* w,int k,int s,int a, int m)
{
	if(s == glfwGetKeyScancode(GLFW_KEY_Z) && a == GLFW_PRESS && (m & GLFW_MOD_CONTROL))
	{
		if(m & GLFW_MOD_SHIFT)
		{
			dispatch(model::key::a_redo());
		}
		else
		{
			dispatch(model::key::a_undo());
		}
	}
	else
	{
		dispatch(model::key::event{k, s, a, m});
	} 
}

void Context::_windowFocusCallback(GLFWwindow* w, int i) 
{
	dispatch(model::window::a_focused{bool(i)});
}


void Context::_framebufferResizeCallback(GLFWwindow *c, int w, int h)
{
	// TODO, decompose these events to be:
	// - NativeWindowResized
	//   - _rebuildSurface
	//   - AppWindowResized
	_rebuildSurface(w, h);
	dispatch(model::window::a_resized{w, h});
	loop();
}
