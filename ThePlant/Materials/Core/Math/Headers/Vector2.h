#pragma once

#include <array>

#include "Core/Math/Headers/Vector.h"

namespace Core {
namespace Math {
  template<typename T>
  struct VectorA<T, 2>
  {
    union {
      struct
      {
        T X;
        T Y;
      };
      std::array<T, 2> XY = {0};
    };

    VectorA()
    {}

    VectorA(const T &d)
      : X(d), Y(d)
    {}

    VectorA(const T &x, const T &y)
      : X(x), Y(y)
    {}

    VectorA(VectorA<T, 2> const &v)
      : X(v.X), Y(v.Y)
    {}

    ~VectorA()
    {
      X.~T();
      Y.~T();
    }

    // methods
    Dimension<2> Dimensions() const
    {
      return Dimension<2>();
    }

    // operators
    VectorA<T, 2> &operator-=(VectorA<T, 2> const &v)
    {
      X -= v.X;
      Y -= v.Y;

      return (*this);
    }

    VectorA<T, 2> &operator+=(VectorA<T, 2> const &v)
    {
      X += v.X;
      Y += v.Y;

      return (*this);
    }

    VectorA<T, 2> &operator*=(T d)
    {
      X *= d;
      Y *= d;

      return (*this);
    }

    VectorA<T, 2> &operator*=(VectorA<T, 2> const &v)
    {
      X *= v.X;
      Y *= v.Y;

      return (*this);
    }

    VectorA<T, 2> &operator/=(T d)
    {
      X /= d;
      Y /= d;

      return (*this);
    }

    VectorA<T, 2> &operator/=(VectorA<T, 2> const &v)
    {
      X /= v.X;
      Y /= v.Y;

      return (*this);
    }

    VectorA<T, 2> &operator=(T d)
    {
      X = d;
      Y = d;

      return (*this);
    }

    // do not need other = operators, since each vector type has the conversion operators
    VectorA<T, 2> &operator=(VectorA<T, 2> const &v)
    {
      if (this != &v) {
        X = v.X;
        Y = v.Y;
      }

      return (*this);
    }

    friend VectorA<T, 2> operator-(VectorA<T, 2> v, T d)
    {
      v -= d;
      return v;
    }

    friend VectorA<T, 2> operator-(VectorA<T, 2> v, VectorA<T, 2> const &oV)
    {
      v -= oV;
      return v;
    }

    friend VectorA<T, 2> operator+(VectorA<T, 2> v, T d)
    {
      v += d;
      return v;
    }

    friend VectorA<T, 2> operator+(VectorA<T, 2> v, VectorA<T, 2> const &oV)
    {
      v += oV;
      return v;
    }

    friend VectorA<T, 2> operator*(VectorA<T, 2> v, T d)
    {
      v *= d;
      return v;
    }

    friend VectorA<T, 2> operator*(VectorA<T, 2> v, VectorA<T, 2> const &oV)
    {
      v *= oV;
      return v;
    }

    friend VectorA<T, 2> operator/(VectorA<T, 2> v, T d)
    {
      v /= d;
      return v;
    }

    friend VectorA<T, 2> operator/(VectorA<T, 2> v, VectorA<T, 2> const &oV)
    {
      v /= oV;
      return v;
    }

    bool operator==(VectorA<T, 2> const &v) const
    {
      return (X == v.X && Y == v.Y);
    }

    bool operator!=(VectorA<T, 2> const &v) const
    {
      return !(*this == v);
    }

    // add in other comparison operators

    T &operator[](int axis)
    {
      return XY[axis];
    }

    T operator[](int axis) const
    {
      return XY[axis];
    }
  };

  /*	TYPE DEFS	*/
  template<typename T>
  using Vector2 = VectorA<T, 2>;

  using Float2 = Vector2<float>;
  using Int2 = Vector2<int>;
  using Uint2 = Vector2<uint>;
}// namespace Math
}// namespace Core