#include "context.h"


using namespace snuifw;

void Context::init()
{
    init_glfw();
    init_skia();

    fill_window_events();    
}

void Context::teardown()
{
    dispatch(model::set_window_action {std::make_shared<model::WindowContainer>(nullptr)});
	glfwTerminate();

    delete sSurface;
	delete sContext;
}

bool Context::is_running()
{
    return glfwWindowShouldClose(window_weak_ref());
}



void Context::init_glfw()
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

	dispatch(model::set_window_action {
		std::make_shared<model::WindowContainer>(window)
	});
}

void Context::init_skia()
{
    GrContextOptions options;
	//options.fRequireDecodeDisableForSRGB = false;
	sContext = GrContext::MakeGL(nullptr, options).release();

	GrGLFramebufferInfo framebufferInfo;
	framebufferInfo.fFBOID = 0; // assume default framebuffer
	// We are always using OpenGL and we use RGBA8 internal format for both RGBA and BGRA configs in OpenGL.
	//(replace line below with this one to enable correct color spaces) framebufferInfo.fFormat = GL_SRGB8_ALPHA8;
	framebufferInfo.fFormat = GL_RGBA8;

	SkColorType colorType;
	if (kRGBA_8888_GrPixelConfig == kSkia8888_GrPixelConfig) {
		colorType = kRGBA_8888_SkColorType;
	}
	else {
		colorType = kBGRA_8888_SkColorType;
	}
	GrBackendRenderTarget backendRenderTarget(_model.window.width, _model.window.height,
		0, // sample count
		0, // stencil bits
		framebufferInfo);

	//(replace line below with this one to enable correct color spaces) sSurface = SkSurface::MakeFromBackendRenderTarget(sContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, SkColorSpace::MakeSRGB(), nullptr).release();
	sSurface = SkSurface::MakeFromBackendRenderTarget(sContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr).release();
	if (sSurface == nullptr) abort();
}

void Context::fill_window_events()
{
	#define DREF ((Context*)glfwGetWindowUserPointer(w))
    glfwSetKeyCallback(window_weak_ref(), [](GLFWwindow* w,int k,int s,int a, int m) {DREF->keyCallback(w, k, s, a, m);});
	glfwSetWindowFocusCallback(window_weak_ref(), [](GLFWwindow* w, int i) {DREF->windowFocusCallback(w, i);});
	glfwSetFramebufferSizeCallback(window_weak_ref(), [](GLFWwindow *w, int x, int y) {DREF->framebufferResizeCallback(w, x, y);});
	#undef DREF
}

void Context::keyCallback(GLFWwindow* w,int k,int s,int a, int m)
{
	if(s == glfwGetKeyScancode(GLFW_KEY_Z) && a == GLFW_PRESS && (m & GLFW_MOD_CONTROL))
	{
		if(m & GLFW_MOD_SHIFT)
		{
			dispatch(model::key_redo());
		}
		else
		{
			dispatch(model::key_undo());
		}
	}
	else
	{
		dispatch(model::key_event{k, s, a, m});
	} 
}

void Context::windowFocusCallback(GLFWwindow* w, int i) 
{
	dispatch(model::window_focused{bool(i)});
}

void Context::framebufferResizeCallback(GLFWwindow *c, int w, int h)
{
	dispatch(model::window_resized{w, h});
}

void Context::dispatch(model::action a)
{
	_model = model::update(_model, a);
}

void Context::wait_events()
{
	glfwWaitEvents();
}

GLFWwindow * Context::window_weak_ref()
{
	return _model.window.window->window();
}