#pragma once

#include <android/native_window_jni.h>

namespace nevo
{
    namespace platform
    {
        namespace android
        {
            class surface_texture_handler
            {
            public:
                virtual ~surface_texture_handler()
                {
                }

                virtual void surface_available(ANativeWindow* window)
                {
                }

                virtual void surface_size_changed()
                {
                }

                virtual void surface_destroyed()
                {
                }
            };

            void initialize();
            surface_texture_handler* create_handler(unsigned int id);
        }
    }
}
