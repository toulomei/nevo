#pragma once

#include <memory>

namespace nevo
{
    namespace opengl
    {
        class context
        {
        public:
            struct configuration
            {
                configuration() : red(8), green(8), blue(8), alpha(8), depth(24), stencil(8), sample_buffers(0), samples(0)
                {
                }

                size_t red, green, blue, alpha, depth, stencil, sample_buffers, samples;
                static const configuration def;
            };

            context(const context&) = delete;
            context& operator=(const context&) = delete;

            context()
            {
            }

            virtual ~context()
            {
            }

            virtual void make_current() = 0;
            virtual void release_current() = 0;
            virtual void swap_buffers() = 0;

            virtual std::unique_ptr<context> create_shared() = 0;
        };

        class context_scope_guard
        {
            context& ctx_;
        public:
            context_scope_guard(const context_scope_guard&) = delete;
            context_scope_guard& operator=(const context_scope_guard&) = delete;

            context_scope_guard(context& ctx) : ctx_(ctx)
            {
                ctx_.make_current();
            }

            ~context_scope_guard()
            {
                ctx_.release_current();
            }
        };
    }
}
