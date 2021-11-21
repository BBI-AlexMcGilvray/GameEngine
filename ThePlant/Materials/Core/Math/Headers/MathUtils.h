#pragma once

#include <cmath>
#include <utility>

#include "Core/Headers/CoreDefs.h"

namespace Core {
namespace Math {
  template <typename T, int POWER>
  constexpr T pow(const T& d)
  {
    if constexpr (POWER == 0)
    {
      return 1;
    }

    return d * pow<T, POWER - 1>(d);
  }

  template<typename T>
  constexpr T sqr(const T& d)
  {
    return pow<T, 2>(d);
  }

  template<typename T>
  T QuadraticFormulaRoot(T a, T b, T c)
  {
    return (sqr(b) - (static_cast<T>(4) * a * c));
  }

  template<typename T>
  std::pair<T, T> QuadraticFormula(T a, T b, T c)
  {
    T additiveResult = ((-b + QuadraticFormulaRoot(a, b, c)) / (static_cast<T>(2) * a));

    return Pair<T>(additiveResult, -additiveResult);
  }
}// namespace Math
}// namespace Core