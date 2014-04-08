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
                public:
                    context(EGLDisplay display_id, EGLConfig config_id, EGLContext shared_context, const EGLint attrib_list[]) : display_id_(display_id), id_(::eglCreateContext(display_id, config_id, shared_context, attrib_list))
                    {
                        if (id_ == EGL_NO_CONTEXT)
                            throw error("eglCreateContext");
                    }
                    ~context()
                    {
                        ::eglDestroyContext(display_id_, id_);
                    }

                    EGLContext id() const
                    {
                        return id_;
                    }

                    operator EGLContext() const
                    {
                        return id();
                    }

                    context(context&&) = default;

                    context(const context&) = delete;
                    context& operator=(const context&) = delete;
                };
            }
        }
    }
}
