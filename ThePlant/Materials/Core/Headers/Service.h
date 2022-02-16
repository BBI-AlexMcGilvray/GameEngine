#pragma once

#include <memory>

#include "Core/Debugging/Headers/Declarations.h"
#include "Core/Debugging/Headers/Macros.h"
#include "Core/Logging/Logger.h"

namespace Core {
template <typename T>
class Service;

template <typename T>
struct ServiceToken
{
    ServiceToken() = default;
    ~ServiceToken()
    {
        if (_instance.use_count() > 1)
        {
            CORE_THROW("ServiceToken", "Deleting service while a reference is still active");
        }

        _instance = nullptr;
    }

    ServiceToken(ServiceToken&&) = default;
    ServiceToken& operator=(ServiceToken&&) = default;

    ServiceToken(const ServiceToken&) = delete;
    ServiceToken& operator=(const ServiceToken&) = delete;

private:
    template <typename T>
    friend class Service;

    ServiceToken(std::shared_ptr<Service<T>> instance)
    : _instance(std::move(instance))
    {}

    std::shared_ptr<Service<T>> _instance;
};

template <typename T>
struct ServiceReference
{
    ServiceReference(std::shared_ptr<Service<T>>& service)
    : _service(service)
    {}

    operator bool() const { return _service != nullptr; }

    // these aren't super pretty, but work
    Core::Ptr<T> operator->() { return &(_service->_service); }
    T& operator*() { return _service->_service; }

private:
    std::shared_ptr<Service<T>> _service;
};

template <typename T>
class Service
{
public:
    Service() = default;

    template <typename ...ARGS>
    static ServiceToken<T> Set(ARGS ...args)
    {
        VERIFY(_instance.expired(), "Overriding an already-set service!");

        std::shared_ptr<Service<T>> instance = std::make_shared<Service<T>>(std::forward<ARGS>(args)...);
        _instance = instance;
        return ServiceToken<T>(std::move(instance));
    }

    static ServiceReference<T> Get()
    {
        return ServiceReference<T>(_instance.lock());
    }

private:
    friend struct ServiceReference<T>;

    inline static std::weak_ptr<Service<T>> _instance;

    template <typename ...ARGS>
    Service(ARGS ...args)
    {
        _service(std::forward<ARGS>(args)...);
    }

    T _service;
};
}// namespace Core

#define SET_SERVICE(TYPE, ...) Core::Service<TYPE>::Set(__VA_ARGS__)
#define GET_SERVICE(TYPE) Core::Service<TYPE>::Get()
#define IF_SERVICE(TYPE) if (auto service = GET_SERVICE(TYPE))
// requires a follow-up parameter withing () brackets
#define WITH_SERVICE(TYPE)  \
    IF_SERVICE(TYPE)    \
    SCOPE

#if DEBUG
#define SET_DEBUG_SERVICE(TYPE, ...) SET_SERVICE(TYPE, __VA_ARGS__)
#define GET_DEBUG_SERVICE(TYPE) GET_SERVICE(TYPE)
#define IF_DEBUG_SERVICE(TYPE) IF_SERVICE(TYPE)
#define WITH_DEBUG_SERVICE(TYPE) WITH_SERVICE(TYPE)
#else
#define SET_DEBUG_SERVICE(TYPE, ...) Core::ServiceToken<TYPE>()
#define GET_DEBUG_SERVICE(TYPE) nullptr
#define IF_DEBUG_SERVICE(TYPE)
#define WITH_DEBUG_SERVICE(TYPE)
#endif
