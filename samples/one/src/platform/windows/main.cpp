#include <nevo/platform/windows/window.h>
#include <nevo/platform/windows/window_class.h>
#include <nevo/platform/windows/message_loop.h>

#include <nevo/platform/windows/opengl/context.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <atomic>

class my_handler : public nevo::platform::windows::default_message_handler
{
    std::unique_ptr<nevo::opengl::context> context;
    float r_, g_, b_;
public:
    typedef nevo::platform::windows::default_message_handler super;

    my_handler(float r, float g, float b)
        : r_(r), g_(g), b_(b)
    {
    }

    LRESULT handle_message(const UINT message, const WPARAM wparam, const LPARAM lparam)
    {
        if (message == WM_DESTROY)
        {
            nevo::platform::windows::message_loop::quit(77);
            return 0;
        }

        if (message == WM_CREATE)
        {
            context.reset(new nevo::platform::windows::opengl::context(handle()));
            context->make_current();
            ::glClearColor(r_, g_, b_, 1.0f);
            context->release_current();
        }

        if (message == WM_LBUTTONDOWN)
        {
            ::DestroyWindow(handle());
            return 0;
        }

        if (context)
        {
            context->make_current();
            ::glClear(GL_COLOR_BUFFER_BIT);
            context->swap_buffers();
            context->release_current();
        }

        return super::handle_message(message, wparam, lparam);
    }
};

int main() {
    nevo::platform::windows::window_class<my_handler> wnd_class("window_class<my_handler>");
    my_handler handler1(1.0f, 1.0f, 0.0f);
    my_handler handler2(1.0f, 0.0f, 0.0f);

    nevo::platform::windows::window wnd1(wnd_class, &handler1, "my window 1", nevo::platform::windows::window::default_style,
        nevo::platform::windows::window::default_x, nevo::platform::windows::window::default_y, 100, 100);
    nevo::platform::windows::window wnd2(wnd_class, &handler2, "my window 2", nevo::platform::windows::window::default_style,
        nevo::platform::windows::window::default_x, nevo::platform::windows::window::default_y, 100, 100);

    std::cout << "EXIT CODE: " << nevo::platform::windows::message_loop::run() << std::endl;
}
