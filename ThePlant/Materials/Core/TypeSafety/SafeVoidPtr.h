#pragma once

#include "../IdTypes/TypeId.h"

namespace Core {
class SafeVoidPtr
{
public:
  SafeVoidPtr()
  {
    _ptr = nullptr;
    _typeId = runtimeId_t();
  }

  template<typename T>
  SafeVoidPtr(T *ptr)
  {
    _ptr = ptr;
    _typeId = GetTypeId<T>();
  }

  SafeVoidPtr(const SafeVoidPtr &other)
  {
    _ptr = other._ptr;
    _typeId = other._typeId;
  }

  SafeVoidPtr &operator=(const SafeVoidPtr &other)
  {
    _ptr = other._ptr;
    _typeId = other._typeId;

    return *this;
  }

  runtimeId_t GetType() const
  {
    return _typeId;
  }

  template<typename T>
  T *Get() const
  {
    if (GetTypeId<T>() == _typeId) {
      return static_cast<T *>(_ptr);
    }

    return nullptr;
  }

  template<typename T>
  T &GetRef() const
  {// may throw, since _ptr could be nullptr
    return *Get<T>();
  }

  template<typename T>
  T *operator->() const
  {
    return Get<T>();
  }

  template<typename T>
  T &operator*() const
  {
    return GetRef<T>();
  }

  template<typename T>
  operator T *() const
  {
    return Get<T>();
  }

  template<typename T>
  operator T &() const
  {
    return GetRef<T>();
  }

private:
  void *_ptr;
  runtimeId_t _typeId;
};
}// namespace Core