#pragma once

#include "SafeVoidPtr.h"

namespace Core {
template<typename T>
class NotNullPtr
{
public:
  NotNullPtr() = delete;
  NotNullPtr(std::nullptr_t) = delete;
  NotNullPtr(T *ptr)
  {
    // assert ptr != nullptr
    _ptr = ptr;
  }

  NotNullPtr(const NotNullPtr &other)
  {// no assert since the other NotNullPtr will never point to null
    _ptr = other._ptr;
  }

  NotNullPtr &operator=(std::nullptr_t) = delete;
  NotNullPtr &operator=(const NotNullPtr &other)
  {
    _ptr = other._ptr;

    return *this;
  }

  T *Get() const
  {
    return _ptr;
  }

  T &GetRef() const
  {
    return *Get();
  }

  T *operator->() const
  {
    return Get();
  }

  T &operator*() const
  {
    return GetRef();
  }

  operator T *() const
  {
    return Get();
  }

private:
  T *_ptr;
};
}// namespace Core
