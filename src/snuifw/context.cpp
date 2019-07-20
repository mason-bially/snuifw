#include "context.h"


using namespace snuifw;

void Context::init()
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

    window = glfwCreateWindow(_model.window.width, _model.window.height, _model.window.name.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

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

    glfwSwapInterval(1);
	//glfwSetKeyCallback(c.window, key_callback);
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