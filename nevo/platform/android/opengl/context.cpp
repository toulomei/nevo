#include <nevo/platform/android/opengl/context.h>
#include <nevo/platform/android/native_window_lock.h>

namespace nevo
{
    namespace platform
    {
        namespace android
        {
            namespace opengl
            {
            }
        }
    }
}

EGLConfig nevo::platform::android::opengl::context::choose_config(EGLDisplay display, const nevo::opengl::context::configuration& conf)
{
    const EGLint config[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, static_cast<int>(conf.red),
        EGL_GREEN_SIZE, static_cast<int>(conf.green),
        EGL_BLUE_SIZE, static_cast<int>(conf.blue),
        EGL_ALPHA_SIZE, static_cast<int>(conf.alpha),
        EGL_DEPTH_SIZE, static_cast<int>(conf.depth),
        EGL_STENCIL_SIZE, static_cast<int>(conf.stencil),
        EGL_SAMPLE_BUFFERS, static_cast<int>(conf.sample_buffers),
        EGL_SAMPLES, static_cast<int>(conf.samples),
        EGL_NONE
    };

    EGLConfig result;
    int configs;

    if (!::eglChooseConfig(display, config, &result, 1, &configs))
        throw error("eglChooseConfig");

    return result;
}

nevo::platform::android::egl::surface nevo::platform::android::opengl::context::create_surface(EGLDisplay display, EGLConfig config, ANativeWindow* window, const configuration& conf)
{
    return egl::surface::create_window_surface(display, config, window, 0);
}

nevo::platform::android::egl::context nevo::platform::android::opengl::context::create_context(EGLDisplay display, EGLConfig config, const configuration& conf)
{
    const EGLint attrib_list[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    return egl::context(display, config, 0, attrib_list);
}

nevo::platform::android::opengl::context::context(ANativeWindow* window, const configuration& conf /*= nevo::opengl::context::configuration::def*/)
    : window_(window), display_(), config_(choose_config(display_, conf)), surface_(create_surface(display_, config_, window, conf)), context_(create_context(display_, config_, conf))
{
}

nevo::platform::android::opengl::context::~context()
{
}

void nevo::platform::android::opengl::context::make_current()
{
}

void nevo::platform::android::opengl::context::release_current()
{
}

void nevo::platform::android::opengl::context::swap_buffers()
{
}

std::unique_ptr<nevo::opengl::context> nevo::platform::android::opengl::context::create_shared()
{
}

void nevo::platform::android::opengl::context::reattach_surface(ANativeWindow* native_window)
{
}

void nevo::platform::android::opengl::context::detach_surface()
{
}
