#pragma once

#include "Core/Math/Headers/Axis.h"
#include "Core/Math/Headers/Basis.h"
#include <cmath>
#include <limits>

namespace Core {
namespace Math {
  constexpr double PI_D = 3.1415926535897;
  constexpr float PI_F = 3.1415927f;
  constexpr int PI_I = 3;

  constexpr double Inf_D = std::numeric_limits<double>::max();
  constexpr float Inf_F = std::numeric_limits<float>::max();
  constexpr int Inf_I = std::numeric_limits<int>::max();

  template<typename int D>
  struct Precision
  {
    const float p = (1.0f / float(D));
    constexpr operator float() const { return p; }
  };
  using Tenth = Precision<10>;
  using Hundredth = Precision<100>;
  using Thousandth = Precision<1000>;
  using DEFAULT_PRECISION = Tenth;

  template<typename int D>
  struct Dimension
  {
    const int d = D;
    constexpr operator int() const { return d; }
  };
  using R1 = Dimension<1>;
  using R2 = Dimension<2>;
  using R3 = Dimension<3>;
  using R4 = Dimension<4>;

  struct II
  {
    const int i = 1;

    template <typename T>
    constexpr operator T() const { return static_cast<T>(i); }
  };

  template <typename T>
  struct Rad;

  template<typename T = float>
  struct Deg
  {
    T Degrees = T(0);

    constexpr Deg(T degrees = T(0))
      : Degrees(degrees)
    {}

    template <typename R>
    constexpr Deg(Rad<R> radians)
      : Degrees(static_cast<T>(radians) * static_cast<T>(180) / static_cast<T>(PI_D))
    {}

    constexpr operator T() const { return Degrees; }
  };

  using FDeg = Deg<float>;
  using DDeg = Deg<double>;

  template <typename T = float>
  struct Rad
  {
    float Radians = 0.0f;

    constexpr Rad(T radians = T(0))
      : Radians(radians)
    {}

    template <typename D>
    constexpr Rad(Deg<D> degrees)
      : Radians(static_cast<T>(degrees) * static_cast<T>(PI_D) / static_cast<T>(180))
    {}

    constexpr operator T() const { return Radians; }
  };

  using FRad = Rad<float>;
  using DRad = Rad<double>;
}// namespace Math
}// namespace Core