#pragma once

#include "Core/Headers/PtrDefs.h"

namespace Core
{
// reference: https://www.codeproject.com/Articles/11015/The-Impossibly-Fast-C-Delegates

// delegate to call member-functions only
template <typename ...ARGS>
class MemberDelegate
{
public:
    Delegate()
    : objectPtr(nullptr)
    , stubFunction(nullptr)
    {}
    
    ~Delegate() = default;

    // make move-only?

    template <typenmame T, void(T::*Method)(ARGS...)>
    static MemberDelegate FromMember(T& object)
    {
        MemberDelegate delegate;
        delegate.objectPtr = &object;
        delegate.stubFunction = &stub_function<T, Method>;

        return delegate;
    }

    void operator()(ARGS ...args) const
    {
        return (*stubFunction)(objectPtr, std::forward<ARGS>(args)...);
    }

private:
    typedef void (*stub_type)(void* objectPtr, ARGS...);

    Ptr<void> objectPtr;
    stub_type stubFunction;

    template <typename T, void(T::*Method)(ARGS...)>
    static void stub_function(Ptr<void> objectPtr, ARGS ...args)
    {
        T& object = *static_cast<Ptr<T>>(objectPtr);
        return object.Method(std::forward<ARGS>(args)...);
    }
};

// delegate to call non-member (or static-member) functions only
// would be nice if we could make this (or a new type) a delegate that can take ANY callable type (though maybe that's just std::function?)
//      - maybe do-able to create a 'MemberDelegate' for a free function by creating one of these and registering the () operator? though how would that manage lifetime?
template <typename ...ARGS>
class Delegate
{
public:
    Delegate()
    : stubFunction(nullptr)
    {}

    ~Delegate() = default;

    // make move-only?

    template <typenmame T, void(*Method)(ARGS...)>
    static Delegate FromFunction()
    {
        Delegate delegate;
        delegate.stubFunction = Method;

        return delegate;
    }

    void operator()(ARGS ...args) const
    {
        return (*stubFunction)(std::forward<ARGS>(args)...);
    }

private:
    typedef void (*stub_type)(ARGS...);

    stub_type stubFunction;
};
} // namespace Core