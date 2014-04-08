#include <nevo/platform/windows/window.h>
#include <sstream>

const unsigned int nevo::platform::windows::window::default_style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
const unsigned int nevo::platform::windows::window::default_x = CW_USEDEFAULT;
const unsigned int nevo::platform::windows::window::default_y = CW_USEDEFAULT;
const unsigned int nevo::platform::windows::window::default_width = CW_USEDEFAULT;
const unsigned int nevo::platform::windows::window::default_height = CW_USEDEFAULT;

nevo::platform::windows::window::~window()
{
    ::DestroyWindow(handle_);
}

void nevo::platform::windows::window::destroy()
{
    if (::DestroyWindow(handle_))
        handle_ = 0;
    else
        throw error("DestroyWindow");
}
