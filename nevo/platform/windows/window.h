#pragma once

#include <nevo/nevo.h>
#include <nevo/platform/windows/window_class.h>

namespace nevo
{
    namespace platform
    {
        namespace windows
        {
            class window
            {
            protected:
                HWND handle_;
            public:
                static const unsigned int default_style;
                static const unsigned int default_x;
                static const unsigned int default_y;
                static const unsigned int default_width;
                static const unsigned int default_height;

                template<typename H>
                window(const window_class<H>& window_class, H* handler, const char * name, unsigned int style = default_style,
                    int x = default_x, int y = default_y, int width = default_width, int height = default_height)
                    : handle_(::CreateWindow(window_class.name(), name, style, x, y, width, height, 0, 0, ::GetModuleHandle(nullptr), handler))
                {
                    if (handle_ == 0)
                        throw error("CreateWindow");
                }
                ~window();

                HWND handle() const
                {
                    return handle_;
                }
                void destroy();

                window(const window&) = delete;
                window& operator=(const window&) = delete;
            };
        }
    }
}
