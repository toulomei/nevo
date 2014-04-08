#pragma once

#include <nevo/nevo.h>
#include <string>

namespace nevo
{
    namespace platform
    {
        namespace windows
        {
            class window_class_base
            {
                const std::string class_name;
            public:
                window_class_base(const std::string& name, WNDPROC wnd_proc, unsigned int style, HICON hicon = 0, HCURSOR hcursor = 0, HBRUSH hbrush = 0, const char * menu_name = nullptr)
                    : class_name(name)
                {
                    WNDCLASS wc = {
                        style,                      // style
                        wnd_proc,                   // WNDPROC
                        0,                          // cbClsExtra
                        0,                          // cbWndExtra
                        ::GetModuleHandle(nullptr), // hInstance
                        hicon,                      // hIcon
                        hcursor,                    // hCursor
                        hbrush,                     // hbrBackground
                        menu_name,                  // lpszMenuName
                        class_name.c_str()          // lpszClassName
                    };

                    if (::RegisterClass(&wc) == 0)
                        throw error("RegisterClass");
                }

                ~window_class_base()
                {
                    ::UnregisterClass(class_name.c_str(), ::GetModuleHandle(nullptr));
                }

                const char * name() const
                {
                    return class_name.c_str();
                }

                window_class_base(const window_class_base&) = delete;
                window_class_base& operator=(const window_class_base&) = delete;
            };

            class default_message_handler
            {
                HWND handle_;
            protected:
                HWND handle() const
                {
                    return handle_;
                }
            public:
                void set_window(HWND handle)
                {
                    handle_ = handle;
                }

                LRESULT handle_message(const UINT message, const WPARAM wparam, const LPARAM lparam)
                {
                    return ::DefWindowProc(handle_, message, wparam, lparam);
                }
            };

            template<typename H = default_message_handler>
            class window_class : public window_class_base
            {
                static H* get_handler_from_wnidow(HWND window)
                {
                    return reinterpret_cast<H*>(::GetWindowLongPtr(window, GWLP_USERDATA));
                }

                static LRESULT CALLBACK wnd_proc(const HWND window, const UINT message, const WPARAM wparam, const LPARAM lparam)
                {
                    if (message == WM_NCCREATE)
                    {
                        CREATESTRUCT *cs = reinterpret_cast<CREATESTRUCT*>(lparam);
                        H& handler = *static_cast<H*>(cs->lpCreateParams);

                        ::SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&handler));

                        handler.set_window(window);
                    }
                    else if (H* handler = get_handler_from_wnidow(window))
                    {
                        return handler->handle_message(message, wparam, lparam);
                    }

                    return ::DefWindowProc(window, message, wparam, lparam);
                }
            public:
                typedef H handler_type;

                explicit window_class(const std::string& name, unsigned int style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC, HICON hicon = 0,
                    HCURSOR hcursor = 0, HBRUSH hbrush = 0, const char * menu_name = nullptr)
                    : window_class_base(name, wnd_proc, style, hicon, hcursor, hbrush, menu_name)
                {
                }

                window_class(const window_class&) = delete;
                window_class& operator=(const window_class&) = delete;
            };
        }
    }
}