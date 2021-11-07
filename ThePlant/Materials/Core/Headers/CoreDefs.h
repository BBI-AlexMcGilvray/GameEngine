#pragma once

namespace Core {
template<typename T>
struct Truth
{
  bool Result;
  T Value;

  Truth(bool result, T value)
    : Result(result), Value(value)
  {}

  operator bool()
  {
    return Result;
  }

  operator T &&()
  {
    return Value;
  }
};

template<typename T>
bool Within(const T& value, const T& basis, const T&variance)
{
  return ((value >= basis - variance) && (value <= basis + variance));
}
template<typename T>
bool InRange(const T& value, const T& min, const T& max)
{
  return ((value >= min) && (value <= max));
}

using uint = unsigned int;
using uint64 = unsigned long int;
using size = size_t;
using byte = unsigned char;
}// namespace Core