#pragma once

#include <android/native_window_jni.h>

namespace nevo
{
    namespace platform
    {
        namespace android
        {
            class native_window_lock
            {
                ANativeWindow* window_;

                native_window_lock(const native_window_lock&);
                native_window_lock& operator=(const native_window_lock&);
            public:
                explicit native_window_lock(ANativeWindow *window) : window_(window)
                {
                    ::ANativeWindow_acquire(window_);
                }

                native_window_lock(JNIEnv *env, jobject surface) : window_(::ANativeWindow_fromSurface(env, surface))
                {
                }

                ~native_window_lock()
                {
                    ::ANativeWindow_release(window_);
                }

                ANativeWindow* id() const {
                    return window_;
                }

                operator ANativeWindow* () const
                {
                    return id();
                }
            };
        }
    }
}
