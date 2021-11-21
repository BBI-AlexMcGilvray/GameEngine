#pragma once

#include <cmath>
#include <utility>

#include "Core/Headers/CoreDefs.h"

namespace Core {
namespace Math {
  namespace {
    template <typename T, int POWER>
    struct PowerOf
    {
        static constexpr T ToThe(const T& base)
        {
            return PowerOf<T, POWER - 1>::ToThe(base) * base;
        }
    };

    template <typename T>
    struct PowerOf<T, 0>
    {
        static constexpr T ToThe(const T& base)
        {
            return 1;
        }
    };
  }

  template <int POWER, typename T>
  constexpr T pow(const T& d)
  {
      return PowerOf<T, POWER>::ToThe(d);
  }

  template<typename T>
  constexpr T sqr(const T& d)
  {
    return pow<2>(d);
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