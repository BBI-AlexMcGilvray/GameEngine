#pragma once

#include <type_traits>

#include "Core/Headers/EnumUtils.h"

template<typename T, typename enabled = void>
struct BitmaskEnum
{
};

template<typename T>
struct BitmaskEnum<T, typename std::enable_if<std::is_enum<T>::value>::type>
{
private:
  using raw_type = std::underlying_type_t<T>;

public:
  BitmaskEnum()
    : _baseEnum(Core::enum_cast<T>(0))
  {
  }

  BitmaskEnum(const T &baseEnum)
    : _baseEnum(baseEnum)
  {
  }

  template <typename ...ARGS>
  BitmaskEnum(const T &val, ARGS ...others)
  {
    SetFlags(val, others...);
  }

  BitmaskEnum(const BitmaskEnum<T> &other)
    : _baseEnum(other._baseEnum)
  {
  }

  BitmaskEnum<T> &operator=(const BitmaskEnum<T> &other)
  {
    _baseEnum = other._baseEnum;

    return *this;
  }

  BitmaskEnum<T> &operator=(const T &other)
  {
    _baseEnum = other;

    return *this;
  }

  bool AnyFlagSet() const
  {
    return (Core::enum_cast(_baseEnum) > 0);
  }

  bool HasAllFlags(const BitmaskEnum<T> &flags) const
  {
    return HasAllFlags(flags._baseEnum);
  }

  bool HasAllFlags(const T &flags) const
  {
    T masked = Core::enum_cast<T>(Core::enum_cast(_baseEnum) & Core::enum_cast(flags));
    return (masked == flags);
  }

  bool AtLeastOneFlag(const BitmaskEnum<T> &flags) const
  {
    return AtLeastOneFlag(flags._baseEnum);
  }

  bool AtLeastOneFlag(const T &flags) const
  {
    raw_type masked = Core::enum_cast(_baseEnum) & Core::enum_cast(flags);
    return (masked > 0);
  }

  void SetFlags(const T& flag)
  {
    _baseEnum = flag;
  }

  template <typename ...ARGS>
  void SetFlags(const T& flag, const ARGS& ...args)
  {
    SetFlags(flag);
    TurnOnFlags(args...);
  }

  void TurnOnFlags(const T& flag)
  {
    *this |= flag;
  }

  template <typename ...ARGS>
  void TurnOnFlags(const T& flag, const ARGS& ...args)
  {
    *this |= flag;
    TurnOnFlags(args...);
  }

  // need a TurnOffFlags function and a ToggleFlags function

  operator T()
  {
    return _baseEnum;
  }

  BitmaskEnum<T> operator&(const BitmaskEnum<T> &other) const
  {
    return ((*this) & other._baseEnum);
  }
  BitmaskEnum<T> operator&(const T &other) const
  {
    return BitmaskEnum<T>(Core::enum_cast<T>(Core::enum_cast(_baseEnum) & Core::enum_cast(other)));
  }
  BitmaskEnum<T> &operator&=(const BitmaskEnum<T> &other)
  {
    return (*this &= other._baseEnum);
  }
  BitmaskEnum<T> &operator&=(const T &other)
  {
    _baseEnum = Core::enum_cast<T>(Core::enum_cast(_baseEnum) & Core::enum_cast(other));

    return *this;
  }

  BitmaskEnum<T> operator|(const BitmaskEnum<T> &other) const
  {
    return ((*this) | other._baseEnum);
  }
  BitmaskEnum<T> operator|(const T &other) const
  {
    return BitmaskEnum<T>(Core::enum_cast<T>(Core::enum_cast(_baseEnum) | Core::enum_cast(other)));
  }
  BitmaskEnum<T> &operator|=(const BitmaskEnum<T> &other)
  {
    return (*this |= other._baseEnum);
  }
  BitmaskEnum<T> &operator|=(const T &other)
  {
    _baseEnum = Core::enum_cast<T>(Core::enum_cast(_baseEnum) | Core::enum_cast(other));

    return *this;
  }

  BitmaskEnum<T> operator^(const BitmaskEnum<T> &other) const
  {
    return ((*this) ^ other._baseEnum);
  }
  BitmaskEnum<T> operator^(const T &other) const
  {
    return BitmaskEnum<T>(Core::enum_cast<T>(Core::enum_cast(_baseEnum) ^ Core::enum_cast(other)));
  }
  BitmaskEnum<T> &operator^=(const BitmaskEnum<T> &other)
  {
    return (*this ^= other._baseEnum);
  }
  BitmaskEnum<T> &operator^=(const T &other)
  {
    _baseEnum = Core::enum_cast<T>(Core::enum_cast(_baseEnum) ^ Core::enum_cast(other));

    return *this;
  }

  BitmaskEnum<T> operator~() const
  {
    raw_type opposite = ~Core::enum_cast(_baseEnum);
    return BitmaskEnum<T>(Core::enum_cast<T>(opposite));
  }

  bool operator==(const BitmaskEnum<T> &other) const
  {
    return (*this == other._baseEnum);
  }
  bool operator==(const T &other) const
  {
    return _baseEnum == other;
  }

  bool operator!=(const BitmaskEnum<T> &other) const
  {
    return !(*this == other);
  }
  bool operator!=(const T &other) const
  {
    return !(*this == other);
  }

private:
  T _baseEnum;
};

template<typename T>
BitmaskEnum<T> operator&(const T &t, const BitmaskEnum<T> &f)
{
  return f & t;
}

// this is useful, put it in later
// template<typename T>
// BitmaskEnum<T> operator|(const T &t1, const T &t2)
// {
//   return t1 | BitmaskEnum<T>(t2);
// }
template<typename T>
BitmaskEnum<T> operator|(const T &t, const BitmaskEnum<T> &f)
{
  return f | t;
}

template<typename T>
BitmaskEnum<T> operator^(const T &t1, const T &t2)
{
  return t1 ^ BitmaskEnum<T>(t2);
}
template<typename T>
BitmaskEnum<T> operator^(const T &t, const BitmaskEnum<T> &f)
{
  return f ^ t;
}