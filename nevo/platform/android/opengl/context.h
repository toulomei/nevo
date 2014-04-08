#pragma once

#include <nevo/nevo.h>
#include <nevo/opengl/context.h>
#include <nevo/platform/android/native_window_lock.h>
#include <nevo/platform/android/egl/display.h>
#include <nevo/platform/android/egl/surface.h>
#include <nevo/platform/android/egl/context.h>

namespace nevo
{
    namespace platform
    {
        namespace android
        {
            namespace opengl
            {
                class context : public nevo::opengl::context
                {
                    native_window_lock window_;

                    egl::display display_;
                    EGLConfig config_;
                    egl::surface surface_;
                    egl::context context_;

                    static EGLConfig choose_config(EGLDisplay display, const configuration& conf);
                    static egl::surface create_surface(EGLDisplay display, EGLConfig config, ANativeWindow* window, const configuration& conf);
                    static egl::context create_context(EGLDisplay display, EGLConfig config, const configuration& conf);
                public:
                    explicit context(ANativeWindow* window, const configuration& conf = nevo::opengl::context::configuration::def);
                    virtual ~context();

                    virtual void make_current();
                    virtual void release_current();
                    virtual void swap_buffers();

                    virtual std::unique_ptr<nevo::opengl::context> create_shared();

                    void reattach_surface(ANativeWindow* native_window);
                    void detach_surface();
                };
            }
        }
    }
}