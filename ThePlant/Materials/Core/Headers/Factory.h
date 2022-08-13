#pragma once

#include <functional>
#include <unordered_map>

#include "Core/Logging/LogFunctions.h"
#include "Core/Headers/Hash.h"
#include "Core/IdTypes/RuntimeId.h"

namespace Core {
template <typename OBJECT, typename KEY, typename ...ARGS>
struct Factory
{
    Factory() = default;
    ~Factory() = default;

    Factory(Factory&&) = default;
    Factory& operator=(Factory&&) = default;

    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;

    template <typename CONSTRUCTOR>
    void Register(KEY&& key, CONSTRUCTOR&& constructor)
    {
    #if DEBUG
        if (_constructors.find(key) != _constructors.end())
        {
            DEBUG_THROW("Factory", "Overwriting a constructor!");
        }
    #endif
        _constructors[key] = std::move(constructor);
    }

    void Unregister(KEY&& key)
    {
    #if DEBUG
        if (_constructors.find(key) == _constructors.end())
        {
            DEBUG_THROW("Factory", "Removing a constructor that doesn't exist!");
        }
    #endif
        _constructors.erase(key);
    }

    OBJECT Create(KEY&& key, ARGS&& ...args)
    {
    #if DEBUG
        if (_constructors.find(key) == _constructors.end())
        {
            DEBUG_THROW("Factory", "Trying to use a constructor that doesn't exist!");
        }
    #endif
        _constructors[key](std::forward<ARGS>(args)...);
    }

private:
    std::unordered_map<KEY, std::function<OBJECT(ARGS...)>> _constructors;
};

template <typename OBJECT, typename ...ARGS>
using TypeFactory = Factory<OBJECT, runtimeId_t, ARGS...>;

template <typename OBJECT, typename ...ARGS>
using HashFactory = Factory<OBJECT, Hash, ARGS...>;
}// namespace Core
