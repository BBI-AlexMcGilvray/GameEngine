#pragma once

#include <type_traits>

template <typename T, typename = std::enable_if<std::is_enum<T>::value>>
int enum_cast(const T& e)
{
    return static_cast<int>(e);
}

template <typename T, typename = std::enable_if<!std::is_enum<T>::value>>
T enum_cast(const int& i)
{
    return static_cast<T>(i);
}

template <typename T, typename enabled = void>
struct FlagEnum{};

template<typename T>
struct FlagEnum<T, typename std::enable_if<std::is_enum<T>::value>::type>
{
public:
  FlagEnum()
  : _baseEnum(enum_cast<T>(0))
  {}

  FlagEnum(const T& baseEnum)
    : _baseEnum(baseEnum)
  {}

  FlagEnum(const FlagEnum<T>& other)
  : _baseEnum(other._baseEnum)
  {}

  FlagEnum<T>& operator=(const FlagEnum<T>& other)
  {
      _baseEnum = other._baseEnum;

      return *this;
  }

  FlagEnum<T>& operator=(const T& other)
  {
      _baseEnum = other;

      return *this;
  }

  bool AnyFlagSet() const
  {
    return (int(_baseEnum) > 0);
  }

  bool HasAllFlags(const FlagEnum<T>& flags) const
  {
    return HasAllFlags(flags._baseEnum);
  }

  bool HasAllFlags(const T& flags) const
  {
    T masked = enum_cast<T>(enum_cast(_baseEnum) & enum_cast(flags));
    return (masked == flags);
  }

  bool AtLeastOneFlag(const FlagEnum<T>& flags) const
  {
    return AtLeastOneFlag(flags._baseEnum);
  }

  bool AtLeastOneFlag(const T& flags) const
  {
    int masked = enum_cast(_baseEnum) & enum_cast(flags);
    return (masked > 0);
  }

  operator T() { return _baseEnum; }

  
  FlagEnum<T> operator &(const FlagEnum<T>& other) const { return ((*this) & other._baseEnum); }
  FlagEnum<T> operator &(const T& other) const
  { 
    return FlagEnum<T>(enum_cast<T>(enum_cast(_baseEnum) & enum_cast(other)));
  }
  FlagEnum<T>& operator &=(const FlagEnum<T>& other)
  {
    return (*this &= other._baseEnum);
  }
  FlagEnum<T>& operator &=(const T& other)
  {
    _baseEnum &= other;

    return *this;
  }

  FlagEnum<T> operator |(const FlagEnum<T>& other) const { return ((*this) | other._baseEnum); }
  FlagEnum<T> operator |(const T& other) const
  {
      return FlagEnum<T>(enum_cast<T>(enum_cast(_baseEnum) | enum_cast(other)));
  }
  FlagEnum<T>& operator|=(const FlagEnum<T>& other)
  {
    return (*this |= other._baseEnum);
  }
  FlagEnum<T>& operator |=(const T& other)
  {
    _baseEnum |= other;

    return *this;
  }

  FlagEnum<T> operator ^(const FlagEnum<T>& other) const { return ((*this) ^ other._baseEnum); }
  FlagEnum<T> operator ^(const T& other) const
  {
      return FlagEnum<T>(enum_cast<T>(enum_cast(_baseEnum) ^ enum_cast(other)));
  }
  FlagEnum<T>& operator ^=(const FlagEnum<T>& other)
  {
    return (*this ^= other._baseEnum);
  }
  FlagEnum<T>& operator ^=(const T& other)
  {
    _baseEnum ^= other;

    return *this;
  }

  FlagEnum<T> operator ~() const
  {
    int opposite = ~enum_cast(_baseEnum);
    return FlagEnum<T>(enum_cast<T>(opposite));
  }

  bool operator==(const FlagEnum<T>& other) const
  {
      return (*this == other._baseEnum);
  }
  bool operator==(const T& other) const
  {
      return _baseEnum == other;
  }

  bool operator!=(const FlagEnum<T>& other) const
  {
      return !(*this == other);
  }
  bool operator!=(const T& other) const
  {
      return !(*this == other);
  }

private:
  T _baseEnum;
};

template <typename T>
FlagEnum<T> operator&(const T& t, const FlagEnum<T>& f) { return f & t; }
template <typename T>
FlagEnum<T> operator|(const T& t, const FlagEnum<T>& f) { return f | t; }
template <typename T>
FlagEnum<T> operator^(const T& t, const FlagEnum<T>& f) { return f ^ t; }