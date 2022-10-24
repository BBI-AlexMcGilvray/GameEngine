#pragma once

#include <memory>

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Logging/LogFunctions.h"

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
            try {
                CORE_THROW("ServiceToken", "Deleting service while a reference is still active");
            }
            catch (...)
            {
                CORE_ERROR("ServiceToken", "Self-caught to avoid destructor warnings, but this is broken!");
            }
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
    ServiceReference() = default;
    ServiceReference(const ServiceReference&) = default;
    ServiceReference(ServiceReference&&) = default;

    ServiceReference& operator=(const ServiceReference&) = default;
    ServiceReference& operator=(ServiceReference&&) = default;

    operator bool() const { return _service != nullptr; }

    // these aren't super pretty, but work
    Core::Ptr<T> operator->() { return &(_service->_service); }
    T& operator*() { return _service->_service; }

private:
    template <typename T>
    friend class Service;

    ServiceReference(std::shared_ptr<Service<T>>& service)
    : _service(service)
    {}

    std::shared_ptr<Service<T>> _service = nullptr;
};

template <typename T>
class Service
{
    struct ConstructionTag{};

public:
    template <typename ...ARGS>
    Service(ConstructionTag tag, ARGS&& ...args)
    : _service(std::forward<ARGS>(args)...)
    {}

    Service(const Service&) = default;
    Service(Service&&) = default;

    Service& operator=(const Service&) = default;
    Service& operator=(Service&&) = default;

    ~Service()
    {
        _instance.reset();
    }

    template <typename ...ARGS>
    static ServiceToken<T> Set(ARGS&& ...args)
    {
        SCOPED_MEMORY_CATEGORY("Service");
        VERIFY(_instance.expired(), "Overriding an already-set service!");

        std::shared_ptr<Service<T>> instance = std::make_shared<Service<T>>(ConstructionTag(), std::forward<ARGS>(args)...);
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
#define IF_DEBUG_SERVICE(TYPE) if (Core::ServiceReference<TYPE> service = Core::ServiceReference<TYPE>())
#define WITH_DEBUG_SERVICE(TYPE) EAT // eat the whole statement so nothing happens
#endif
