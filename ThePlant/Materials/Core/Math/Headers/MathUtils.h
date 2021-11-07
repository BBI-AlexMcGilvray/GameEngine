#pragma once

#include <cmath>
#include <utility>

#include "Core/Headers/CoreDefs.h"

namespace Core {
namespace Math {
  template<typename T>
  T Sqr(T a)
  {
    return (a * a);
  }

  template<typename T>
  T Sqrt(T a)
  {
    return sqrt(a);
  }

  template<typename T>
  T Cos(T a)
  {
    return cos(a);
  }

  template<typename T>
  T Acos(T a)
  {
    return acos(a);
  }

  template<typename T>
  T Sin(T a)
  {
    return sin(a);
  }

  template<typename T>
  T Asin(T a)
  {
    return asin(a);
  }

  template<typename T>
  T Tan(T a)
  {
    return tan(a);
  }

  template<typename T>
  T Atan(T a)
  {
    return atan(a);
  }

  template<typename T>
  T QuadraticFormulaRoot(T a, T b, T c)
  {
    return (Sqr(b) - (T(4) * a * c));
  }

  template<typename T>
  std::pair<T, T> QuadraticFormula(T a, T b, T c)
  {
    T additiveResult = ((-b + QuadraticFormulaRoot(a, b, c)) / (T(2) * a));

    return Pair<T>(additiveResult, -additiveResult);
  }
}// namespace Math
}// namespace Core