#pragma once

#include <nevo/opengl/context.h>
#include <nevo/platform/windows/window.h>

namespace nevo
{
    namespace platform
    {
        namespace windows
        {
            namespace opengl
            {
                class context : public nevo::opengl::context
                {
                    class dc_holder
                    {
                        HWND window_;
                        HDC dc;
                    public:
                        dc_holder(HWND window);
                        ~dc_holder();

                        dc_holder(const dc_holder&) = delete;
                        dc_holder& operator=(const dc_holder&) = delete;


                        operator HDC() const
                        {
                            return dc;
                        }
                    };

                    class glrc_holder
                    {
                        HGLRC glrc;
                    public:
                        explicit glrc_holder(HDC dc);
                        ~glrc_holder();

                        glrc_holder(const glrc_holder&) = delete;
                        glrc_holder& operator=(const glrc_holder&) = delete;

                        glrc_holder(glrc_holder&& src)
                            : glrc(std::move(src.glrc))
                        {
                            src.glrc = 0;
                        }

                        operator HGLRC() const
                        {
                            return glrc;
                        }
                    };

                    class initializer;

                    bool initialized;
                    dc_holder dc;
                    glrc_holder rc;

                    static bool initialize();
                    static glrc_holder create_glrc(HDC dc, const configuration& conf);
                public:
                    explicit context(HWND window, const configuration& conf = nevo::opengl::context::configuration::def);
                    virtual ~context();

                    virtual void make_current();
                    virtual void release_current();
                    virtual void swap_buffers();

                    virtual std::unique_ptr<nevo::opengl::context> create_shared();
                };
            }
        }
    }
}