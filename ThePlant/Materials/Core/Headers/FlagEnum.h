#pragma once

#include "Core/Headers/TemplateDefs.h"

namespace Core {
template<typename T>
using IsEnum = typename EnableIf<std::is_enum<T>::value, int>::type;

// use when an enum is being used as flags or an enum can hold multiple states
template<typename T, IsEnum<T> = 0>
struct FlagEnum
{
public:
  FlagEnum(T baseEnum)
    : _baseEnum(baseEnum)
  {}

  bool AnyFlagSet() const
  {
    return (int(_baseEnum) > 0);
  }

  bool HasAllFlags(const FlagEnum<T>& flags) const
  {
    return ((_baseEnum & flags) == _baseEnum);
  }

  bool HasAllFlags(const T& flags) const
  {
    return ((_baseEnum & flags) == _baseEnum);
  }

  bool AtLeastOneFlag(const FlagEnum<T>& flags) const
  {
    return (int(_baseEnum & flags) > 0);
  }

  bool AtLeastOneFlag(const T& flags) const
  {
    return (int(_baseEnum & flags) > 0);
  }

  operator T() { return _baseEnum; }

  
  FlagEnum<T> operator &(const FlagEnum<T>& other) { return FlagEnum<T>(_baseEnum & other._baseEnum); }
  FlagEnum<T> operator &(const T& other) { return FlagEnum<T>(_baseEnum & other); }
  FlagEnum<T>& operator &=(const FlagEnum<T>& other)
  {
    _baseEnum &= other._baseEnum;

    return *this;
  }
  FlagEnum<T>& operator &=(const T& other)
  {
    _baseEnum &= other;

    return *this;
  }

  FlagEnum<T> operator |(const FlagEnum<T>& other) { return FlagEnum<T>(_baseEnum | other._baseEnum); }
  FlagEnum<T> operator |(const T& other) { return FlagEnum<T>(_baseEnum | other); }
  FlagEnum<T>& operator|=(const FlagEnum<T>& other)
  {
    _baseEnum |= other._baseEnum;

    return *this;
  }
  FlagEnum<T>& operator |=(const T& other)
  {
    _baseEnum |= other;

    return *this;
  }

  FlagEnum<T> operator ^(const FlagEnum<T>& other) { return FlagEnum<T>(_baseEnum ^ other._baseEnum); }
  FlagEnum<T> operator ^(const T& other) { return FlagEnum<T>(_baseEnum ^ other); }
  FlagEnum<T>& operator ^=(const FlagEnum<T>& other)
  {
    _baseEnum ^= other._baseEnum;

    return *this;
  }
  FlagEnum<T>& operator ^=(const T& other)
  {
    _baseEnum ^= other;

    return *this;
  }

  FlagEnum<T> operator ~() { return FlagEnum<T>(~_baseEnum); }

private:
  T _baseEnum;
};
}// namespace Core