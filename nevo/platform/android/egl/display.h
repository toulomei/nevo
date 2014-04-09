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
                class display
                {
                    EGLDisplay id_;
                    EGLint major_version_, minor_version_;

                    display(const display&) = delete;
                    display& operator=(const display&) = delete;
                public:
                    explicit display(EGLNativeDisplayType display_id = EGL_DEFAULT_DISPLAY) : id_(::eglGetDisplay(display_id))
                    {
                        if (id_ == EGL_NO_DISPLAY)
                            throw error("eglGetDisplay");
                        
                        if (!::eglInitialize(id_, &major_version_, &minor_version_))
                            throw error("eglInitialize");
                    }

                    display(display&& other) : id_(other.id_), major_version_(other.major_version_), minor_version_(other.minor_version_)
                    {
                        other.id_ = 0;
                    }

                    ~display()
                    {
                        if (id_)
                            ::eglTerminate(id_);
                    }

                    display& operator=(display&& other)
                    {
                        id_ = other.id_;
                        major_version_ = other.major_version_;
                        minor_version_ = other.minor_version_;

                        other.id_ = 0;
                    }

                    EGLint major_version() const
                    {
                        return major_version_;
                    }

                    EGLint minor_version() const
                    {
                        return minor_version_;
                    }

                    EGLDisplay id() const
                    {
                        return id_;
                    }

                    operator EGLDisplay() const
                    {
                        return id();
                    }
                };
            }
        }
    }
}
