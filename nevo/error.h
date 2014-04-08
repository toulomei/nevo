#pragma once

#include <stdexcept>

namespace nevo
{
    class error : public std::runtime_error
    {
    public:
        error(const std::string& message) : std::runtime_error(message)
        {
        };
    };
}
