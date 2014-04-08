#pragma once

#include <nevo/nevo.h>

#include <windows.h>

namespace nevo
{
    namespace platform
    {
        namespace windows
        {
            namespace message_loop
            {
                bool is_message_pending()
                {
                    MSG msg;
                    return ::PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE) == TRUE;
                }

                static std::pair<bool, int> run_once(bool wait = true)
                {
                    MSG msg;
                    if (int ret = ::GetMessage(&msg, 0, 0, 0) != 0)
                    {
                        if (ret == -1)
                            throw ("GetMessage()");

                        ::TranslateMessage(&msg);
                        ::DispatchMessage(&msg);

                        return std::make_pair(false, 0);
                    }
                    else
                        return std::make_pair(true, msg.wParam);
                }

                int run()
                {
                    MSG msg;
                    while (int ret = ::GetMessage(&msg, 0, 0, 0) != 0)
                    {
                        if (ret == -1)
                            throw ("GetMessage()");

                        ::TranslateMessage(&msg);
                        ::DispatchMessage(&msg);
                    }

                    return msg.wParam;
                }

                template<typename H>
                int run(H h)
                {
                    MSG msg;
                    while (true)
                    {
                        if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
                        {
                            if (msg.message == WM_QUIT)
                                break;

                            ::TranslateMessage(&msg);
                            ::DispatchMessage(&msg);
                        }
                        else
                            h();
                    }

                    return msg.wParam;
                }

                typedef DWORD id;

                void quit(int exit_code)
                {
                    ::PostQuitMessage(exit_code);
                }

                void quit(id loop_id, int exit_code)
                {
                    if (::PostThreadMessage(loop_id, WM_QUIT, exit_code, 0) == 0)
                        throw error("PostThreadMessage");
                }
            }
        }
    }
}
