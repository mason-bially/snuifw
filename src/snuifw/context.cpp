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
    glfwDestroyWindow(window);
	glfwTerminate();

    delete sSurface;
	delete sContext;
}

bool Context::is_running()
{
    return glfwWindowShouldClose(window);
}



void Context::init_glfw()
{
    if (!glfwInit()) {
		throw std::runtime_error("GLFW Problem Bro");
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//(uncomment to enable correct color spaces) glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
		glfwWindowHint(GLFW_STENCIL_BITS, 0);
		//glfwWindowHint(GLFW_ALPHA_BITS, 0);
		glfwWindowHint(GLFW_DEPTH_BITS, 0);

		window = glfwCreateWindow(_model.window.width, _model.window.height, _model.window.name.c_str(), NULL, NULL);
		if (!window) {
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
	glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);		
    glfwSwapInterval(1);
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
    glfwSetKeyCallback(window, [](GLFWwindow* w,int k,int s,int a, int m) {
        auto this_ = (Context*)glfwGetWindowUserPointer(w);
		if(s == glfwGetKeyScancode(GLFW_KEY_Z) && a == GLFW_PRESS && (m & GLFW_MOD_CONTROL))
		{
			if(m & GLFW_MOD_SHIFT)
			{
				this_->_model = model::update(this_->_model, model::key_redo());
			}
			else
			{
				this_->_model = model::update(this_->_model, model::key_undo());
			}
		}
		else
		{
			this_->_model = model::update(this_->_model, model::key_event{k, s, a, m});
		} 
        //this_->_model
    });
}