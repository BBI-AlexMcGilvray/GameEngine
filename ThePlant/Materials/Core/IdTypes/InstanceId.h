#pragma once

#include <cstdint>

namespace Core {
namespace InstanceId_Helper {
  constexpr uint32_t INVALID_ID = 0;

  template <typename ID_TYPE>
  uint32_t GetNextId()
  {
      static uint32_t next_id = 1;
      return next_id++;
  }
} // namespace InstanceId_Helper

template <typename ID_TYPE>
struct instanceId;

template <typename ID_TYPE>
instanceId<ID_TYPE> GetInstanceId();

template <typename ID_TYPE>
struct instanceIdHasher;

// all ids of the same ID_TYPE increment the hidden counter - each is unique for the given ID_TYPE (unless there is overflow)
// i.e. instanceId<Type> may equal instanceId<Class>, but instanceId<Type> will never equal another instanceId<Type> (unless they are copied/moved)
template<typename ID_TYPE>
struct instanceId
{
  template <typename ID_TYPE>
  friend instanceId<ID_TYPE> GetInstanceId();

  template <typename ID_TYPE>
  friend struct instanceIdHasher;

  constexpr instanceId()
  : _id(InstanceId_Helper::INVALID_ID)
  {}

  constexpr instanceId(const instanceId &rhs)
    : _id(rhs._id)
  {}

  constexpr instanceId &operator=(const instanceId &rhs)
  {
    _id = rhs._id;
    return *this;
  }

  constexpr bool IsValid() const
  {
    return _id != InstanceId_Helper::INVALID_ID;
  }

  constexpr bool operator==(const instanceId<ID_TYPE> &other) const
  {
    return _id == other._id;
  }

  constexpr bool operator!=(const instanceId<ID_TYPE> &other) const
  {
    return !(*this == other);
  }

protected:
  enum Constructor {
    NEW
  };

  instanceId(Constructor)
    : _id(InstanceId_Helper::GetNextId<ID_TYPE>()) // post so that id '1' gets used
  {}

private:
  uint32_t _id;
};

template <typename ID_TYPE>
instanceId<ID_TYPE> GetInstanceId() { return instanceId<ID_TYPE>(instanceId<ID_TYPE>::Constructor::NEW); }

template <typename ID_TYPE>
struct instanceIdHasher
{
    size_t operator()(const Core::instanceId<ID_TYPE>& id) const
    {
        return id._id;
    }
};
}// namespace Core