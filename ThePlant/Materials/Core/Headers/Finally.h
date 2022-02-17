#pragma once

#include <functional>

namespace Core {
struct Finally
{
    Finally(std::function<void()>&& callback)
    : _callback(std::move(callback))
    {}

    Finally() = default;
    Finally(Finally&&) = default;
    Finally& operator=(Finally&&) = default;

    Finally(const Finally&) = delete;
    Finally& operator=(const Finally&) = delete;

    ~Finally()
    {
        if (_callback)
        {
            _callback();
        }
    }

private:
    std::function<void()> _callback;
};
}// namespace Core
