#include <nevo/platform/windows/opengl/context.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/wglew.h>

namespace nevo
{
    namespace platform
    {
        namespace windows
        {
            namespace opengl
            {
                class context::initializer
                {
                public:
                    initializer()
                    {
                        window_class<> dummy_wnd_class("nevo::platform::windows::opengl::context::initializer");
                        window_class<>::handler_type handler;

                        window wnd(dummy_wnd_class, &handler, "", WS_OVERLAPPEDWINDOW);

                        PIXELFORMATDESCRIPTOR pfd = {
                            sizeof(PIXELFORMATDESCRIPTOR),             // Size Of This Pixel Format Descriptor
                            1,                                         // Version Number
                            PFD_DRAW_TO_WINDOW |                       // Format Must Support Window
                            PFD_SUPPORT_OPENGL |                       // Format Must Support OpenGL
                            PFD_DOUBLEBUFFER,                          // Must Support Double Buffering
                            PFD_TYPE_RGBA,                             // Request An RGBA Format
                            32,
                            0, 0, 0, 0, 0, 0,                          // Color Bits Ignored
                            0,                                         // No Alpha Buffer
                            0,                                         // Shift Bit Ignored
                            0,                                         // No Accumulation Buffer
                            0, 0, 0, 0,                                // Accumulation Bits Ignored
                            24,                                        // Z-Buffer (Depth Buffer)
                            8,                                         // Stencil Buffer Depth
                            0,                                         // No Auxiliary Buffer
                            PFD_MAIN_PLANE,                            // Main Drawing Layer
                            0,                                         // Reserved
                            0, 0, 0                                    // Layer Masks Ignored
                        };

                        dc_holder dc(wnd.handle());

                        GLuint pf = ::ChoosePixelFormat(dc, &pfd);
                        if (!pf)
                            throw nevo::platform::windows::error("ChoosePixelFormat()");

                        if (!::DescribePixelFormat(dc, pf, sizeof(pfd), &pfd))
                            throw nevo::platform::windows::error("DescribePixelFormat()");

                        if (!::SetPixelFormat(dc, pf, &pfd))
                            throw nevo::platform::windows::error("SetPixelFormat()");

                        glrc_holder rc(dc);

                        if (!::wglMakeCurrent(dc, rc))
                            throw nevo::platform::windows::error("wglMakeCurrent()");

                        glewExperimental = GL_TRUE;
                        if (::glewInit() != GLEW_OK)
                            throw nevo::platform::windows::opengl::error("glewInit()");
                    }

                    initializer(const initializer&) = delete;
                    initializer& operator=(const initializer&) = delete;
                };

            }
        }
    }
}

void nevo::platform::windows::opengl::context::make_current()
{
    if (!::wglMakeCurrent(dc, rc))
        throw nevo::platform::windows::error("wglMakeCurrent()");
}

void nevo::platform::windows::opengl::context::release_current()
{
    if (!::wglMakeCurrent(0, 0))
        throw nevo::platform::windows::error("wglMakeCurrent()");
}

void nevo::platform::windows::opengl::context::swap_buffers()
{
    if (!::SwapBuffers(dc))
        throw nevo::platform::windows::error("SwapBuffers()");
}

std::unique_ptr<nevo::opengl::context> nevo::platform::windows::opengl::context::create_shared()
{
    throw std::runtime_error("not implemented");
}

nevo::platform::windows::opengl::context::context(HWND window, const configuration& conf)
    : initialized(initialize()), dc(window), rc(create_glrc(dc, conf))
{
}

nevo::platform::windows::opengl::context::~context()
{
}

nevo::platform::windows::opengl::context::glrc_holder nevo::platform::windows::opengl::context::create_glrc(HDC dc, const configuration& conf)
{
    const int attribList[] =
    {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_RED_BITS_ARB, conf.red,
        WGL_GREEN_BITS_ARB, conf.green,
        WGL_BLUE_BITS_ARB, conf.blue,
        WGL_ALPHA_BITS_ARB, conf.alpha,
        WGL_DEPTH_BITS_ARB, conf.depth,
        WGL_STENCIL_BITS_ARB, conf.stencil,
        WGL_SAMPLE_BUFFERS_ARB, conf.sample_buffers,
        WGL_SAMPLES_ARB, conf.samples,
        0
    };

    int pf;
    unsigned int pf_count;
    ::wglChoosePixelFormatARB(dc, attribList, nullptr, 1, &pf, &pf_count);
    if (!pf_count)
        throw nevo::platform::windows::error("wglChoosePixelFormatARB()");

    PIXELFORMATDESCRIPTOR pfd;
    if (!::DescribePixelFormat(dc, pf, sizeof(pfd), &pfd))
        throw nevo::platform::windows::error("DescribePixelFormat()");

    if (!::SetPixelFormat(dc, pf, &pfd))
        throw nevo::platform::windows::error("SetPixelFormat()");

    return glrc_holder(dc);
}

bool nevo::platform::windows::opengl::context::initialize()
{
    static initializer glew_initializer;
    return true;
}

nevo::platform::windows::opengl::context::dc_holder::dc_holder(HWND window)
    : window_(window), dc(::GetDC(window))
{
    if (!dc)
        throw nevo::platform::windows::error("GetDC()");
}

nevo::platform::windows::opengl::context::dc_holder::~dc_holder()
{
    ::ReleaseDC(window_, dc);
}

nevo::platform::windows::opengl::context::glrc_holder::glrc_holder(HDC dc)
    : glrc(::wglCreateContext(dc))
{
    if (!glrc)
        throw nevo::platform::windows::error("wglCreateContext()");
}

nevo::platform::windows::opengl::context::glrc_holder::~glrc_holder()
{
    if (glrc)
        ::wglDeleteContext(glrc);
}
