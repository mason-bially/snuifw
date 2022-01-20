#include "skia.h"
#include "snuifw/snuifw.h"

using namespace snuifw::skia;

DrawWindow::DrawWindow(snuifw::Context* context)
{
    _snuifw = context;
    _window = context->getWindow();
}

DrawWindow::~DrawWindow()
{

}

void DrawWindow::prepareContext(int width, int height)
{
    GrContextOptions options;
    //options.fRequireDecodeDisableForSRGB = false;
    _context = GrDirectContext::MakeGL(nullptr, options).release();
    
    _frameBuffer = GrGLFramebufferInfo();
    _renderTarget = GrBackendRenderTarget();

    if (!rebuildSurface(width, height))
        throw std::runtime_error("Could not initalize surface.");
}


bool DrawWindow::rebuildSurface(int width, int height)
{
    if (_surface != nullptr)
        delete _surface;

    _frameBuffer.fFBOID = 0; // assume default framebuffer
    // We are always using OpenGL and we use RGBA8 internal format for both RGBA and BGRA configs in OpenGL.
    //(replace line below with this one to enable correct color spaces) framebufferInfo.fFormat = GL_SRGB8_ALPHA8;
    _frameBuffer.fFormat = GL_RGBA8;

    SkColorType colorType = kRGBA_8888_SkColorType;
    //if (kRGBA_8888_GrPixelConfig == kSkia8888_GrPixelConfig) {
    //	colorType = kRGBA_8888_SkColorType;
    //}
    //else {
    //	colorType = kBGRA_8888_SkColorType;
    //}

    _renderTarget = GrBackendRenderTarget(
        width, height,
        4, // sample count
        0, // stencil bits
        _frameBuffer);

    //(replace line below with this one to enable correct color spaces) _surface = SkSurface::MakeFromBackendRenderTarget(_TopContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, SkColorSpace::MakeSRGB(), nullptr).release();
    _surface = SkSurface::MakeFromBackendRenderTarget(_context, _renderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr).release();
    return _surface != nullptr;
}