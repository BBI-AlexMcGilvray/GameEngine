#pragma once

#include <cstdint>

namespace Core {
  namespace TypeId_Helper {
    constexpr inline uint32_t INVALID_ID = 0;
    extern uint32_t next_id;
  }

template<typename T>
struct runtimeId;

struct runtimeId_t
{
  template<typename T>
  friend struct runtimeId;

  friend runtimeId_t MakeTypeId(uint32_t);

  constexpr runtimeId_t()
    : _id(TypeId_Helper::INVALID_ID)
  {}

  constexpr runtimeId_t(const runtimeId_t &rhs)
    : _id(rhs._id)
  {}

  constexpr runtimeId_t &operator=(const runtimeId_t &other)
  {
    _id = other._id;
    return *this;
  }

  constexpr bool IsValid() const
  {
    return _id == TypeId_Helper::INVALID_ID;
  }

  constexpr bool operator==(const runtimeId_t &other) const
  {
    return _id == other._id;
  }

  constexpr bool operator!=(const runtimeId_t &other) const
  {
    return !(*this == other);
  }

  constexpr operator uint32_t() const
  {
    return _id;
  }

protected:
  runtimeId_t(uint32_t id)
    : _id(id)
  {}

private:
  uint32_t _id;
};

template<typename T>
struct runtimeId
{
  template<typename T2>
  friend runtimeId_t GetTypeId();

  constexpr runtimeId() = default;

  constexpr runtimeId(const runtimeId &rhs)
    : _t(rhs._t)
  {}

  constexpr runtimeId &operator=(const runtimeId &rhs)
  {
    _t = rhs._t;
    return *this;
  }
  
  constexpr bool IsValid() const
  {
    return _t.IsValid();
  }

  constexpr bool operator==(const runtimeId &other) const
  {
    return _t == other._t;
  }

  constexpr bool operator!=(const runtimeId &other) const
  {
    return !(*this == other);
  }

  constexpr operator runtimeId_t() const
  {
    return _t;
  }

protected:
  enum Constructor {
    NEW
  };

  runtimeId(Constructor)
    : _t(TypeId_Helper::next_id++) // post so that id '1' gets used
  {}

private:
  runtimeId_t _t;
};

template<typename T>
inline runtimeId_t GetTypeId()
{
  // must make sure this strips T down to the absolute base type
  static runtimeId<T> id(runtimeId<T>::Constructor::NEW);
  return id;
}

inline runtimeId_t MakeTypeId(uint32_t id)
{
  return runtimeId_t(id);
}
}// namespace Core