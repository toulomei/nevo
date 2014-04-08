#pragma once

#include <nevo/nevo.h>
#include <EGL/egl.h>

namespace nevo
{
    namespace platform
    {
        namespace android
        {
            namespace egl
            {
                class surface
                {
                    EGLDisplay display_id_;
                    EGLSurface id_;

                    surface(EGLDisplay display_id, EGLSurface id) : display_id_(display_id), id_(id)
                    {
                        if (id_ == EGL_NO_SURFACE)
                            throw error("eglCreateSurface");
                    }
                public:
                    static surface create_window_surface(EGLDisplay display_id, EGLConfig config_id, EGLNativeWindowType window, const EGLint attrib_list[])
                    {
                        return surface(display_id, ::eglCreateWindowSurface(display_id, config_id, window, attrib_list));
                    }

                    static surface create_pbuffer_surface(EGLDisplay display_id, EGLConfig config_id, const EGLint attrib_list[])
                    {
                        return surface(display_id, ::eglCreatePbufferSurface(display_id, config_id, attrib_list));
                    }

                    ~surface()
                    {
                        ::eglDestroySurface(display_id_, id_);
                    }

                    EGLSurface id() const
                    {
                        return id_;
                    }

                    operator EGLSurface() const
                    {
                        return id();
                    }

                    surface(surface&&) = default;

                    surface(const surface&) = delete;
                    surface& operator=(const surface&) = delete;
                };
            }
        }
    }
}
