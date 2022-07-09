#pragma once

#include "Core/Math/Headers/MathDefs.h"
#include "Core/Random/Random.h"
#include <cmath>
#include <type_traits>

namespace Core {
// returns between 0 and max
template<typename T>
auto LessThan(Random &random, const T &max) -> typename std::enable_if<!std::is_floating_point<T>::value, T>::type
{
  // assert(max <= INT32_MAX); // largest random value that can be generated is INT32_MAX
  return random.Next<T>() % max;
}

// returns between 0 and max
template<typename T>
auto LessThan(Random &random, const T &max) -> typename std::enable_if<std::is_floating_point<T>::value, T>::type
{
  // since floating point values will always be within 0 and 1
  return random.Next<T>() * max;
}

template<typename T>
T InRange(Random &random, const T &min, const T &max)
{
  // negatives work because of the min + LessThan(...) will lower the values if min is negative
  // assert max >= min
  // assert max - min < INT32_MAX since that is the max we can generate
  return min + LessThan(random, max - min);
}

bool XInY(Random &random, const std::uint32_t &x, const std::uint32_t &y)
{
  // assert(x < y);
  // assert(y <= INT32_MAX); // largest random value that can be generated is INT32_MAX
  return ((random.Next<uint32_t>() % y) <= x);
}

bool OneInX(Random &random, const std::uint32_t &x)
{
  // assert(x <= INT32_MAX); // largest random value that can be generated is INT32_MAX
  return XInY(random, 1, x);
}

// http://dspguide.com/ch2/6.htm
// defaults to mean of 0 and standard deviation of 1
template<typename T>
T NormalDistribution(Random &random)
{
  T r1 = InRange<T>(random, T(0), T(1));
  T r2 = InRange<T>(random, T(0), T(1));

  return std::sqrt(T(-2) * log(r1)) * std::cos(T(2) * T(PI_D) * r2);
}

// http://dspguide.com/ch2/6.htm
template<typename T>
T NormalDistribution(Random &random, const T &mean, const T &standardDeviation)
{
  return (NormalDistribution<T>(random) * standardDeviation) + mean;
}
}// namespace Core