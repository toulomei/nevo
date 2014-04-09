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
                class context
                {
                    EGLDisplay display_id_;
                    EGLContext id_;

                    context(const context&) = delete;
                    context& operator=(const context&) = delete;
                public:
                    context(EGLDisplay display_id, EGLConfig config_id, EGLContext shared_context, const EGLint attrib_list[]) : display_id_(display_id), id_(::eglCreateContext(display_id, config_id, shared_context, attrib_list))
                    {
                        if (id_ == EGL_NO_CONTEXT)
                            throw error("eglCreateContext");
                    }

                    context(context&& other) : display_id_(other.display_id_), id_(other.id_)
                    {
                        other.id_ = 0;
                    }

                    ~context()
                    {
                        if (id_)
                            ::eglDestroyContext(display_id_, id_);
                    }

                    context& operator=(context&& other)
                    {
                        display_id_ = other.display_id_;
                        id_ = other.id_;
                        other.id_ = 0;
                    }

                    EGLContext id() const
                    {
                        return id_;
                    }

                    operator EGLContext() const
                    {
                        return id();
                    }
                };
            }
        }
    }
}
