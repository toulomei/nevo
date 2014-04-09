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

                    surface(const surface&) = delete;
                    surface& operator=(const surface&) = delete;
                public:
                    static surface create_window_surface(EGLDisplay display_id, EGLConfig config_id, EGLNativeWindowType window, const EGLint attrib_list[])
                    {
                        return surface(display_id, ::eglCreateWindowSurface(display_id, config_id, window, attrib_list));
                    }

                    static surface create_pbuffer_surface(EGLDisplay display_id, EGLConfig config_id, const EGLint attrib_list[])
                    {
                        return surface(display_id, ::eglCreatePbufferSurface(display_id, config_id, attrib_list));
                    }

                    surface(surface&& other) : display_id_(other.display_id_), id_(other.id_)
                    {
                        other.id_ = 0;
                    }

                    ~surface()
                    {
                        if (id_)
                            ::eglDestroySurface(display_id_, id_);
                    }

                    surface& operator=(surface&& other)
                    {
                        display_id_ = other.display_id_;
                        id_ = other.id_;
                        other.id_ = 0;
                    }

                    EGLSurface id() const
                    {
                        return id_;
                    }

                    operator EGLSurface() const
                    {
                        return id();
                    }
                };
            }
        }
    }
}
