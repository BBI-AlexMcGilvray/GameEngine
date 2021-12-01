#pragma once

#include <cstdint>

namespace Core {
namespace {
  constexpr uint32_t INVALID_ID = 0;
  static uint32_t next_id = 1;

  template <typename ID_TYPE>
  ID_TYPE GetNewId()
  {
      static ID_TYPE current_ID = 0;
      return ++current_ID;
  }
}// namespace

// all ids of the same ID_TYPE increment the hidden counter - each is unique for the given ID_TYPE (unless there is overflow)
// i.e. instanceId<int> may equal instanceId<float>, but instanceId<int> will never equal another instanceId<int> (unless they are copied/moved)
template<typename ID_TYPE>
struct instanceId
{
  constexpr instanceId()
  : _id(GetNewId<ID_TYPE>())
  {}

  constexpr instanceId(const instanceId &rhs)
    : _id(rhs._id)
  {}

  constexpr instanceId &operator=(const instanceId &rhs)
  {
    _id = rhs._id;
    return *this;
  }

  constexpr bool operator==(const runtimeId &other)
  {
    return _id == other._id;
  }

  constexpr bool operator!=(const runtimeId &other)
  {
    return _id == other._id;
  }

private:
  ID_TYPE _id;
};

template <typename ID_TYPE>
instanceId<ID_TYPE> GetInstanceId() { return instanceId<ID_TYPE>(); }
}// namespace Core