#pragma once

#include <array>

#include "Core/Math/Headers/Vector2.h"

namespace Core {
namespace Math {
  template<typename T>
  struct VectorA<T, 3>
  {
    union {
      struct
      {
        union {
          struct
          {
            T X;
            T Y;
          };
          Vector2<T> XY;
        };
        T Z;
      };
      std::array<T, 3> XYZ = {0};
    };

    VectorA()
    {}

    VectorA(const T &d)
      : X(d), Y(d), Z(d)
    {}

    VectorA(const T &x, const T &y, const T &z)
      : X(x), Y(y), Z(z)
    {}

    VectorA(VectorA<T, 2> const &v, const T &d1 = 0)
      : XY(v), Z(d1)
    {}

    VectorA(VectorA<T, 3> const &v)
      : X(v.X), Y(v.Y), Z(v.Z)
    {}

    ~VectorA()
    {
      X.~T();
      Y.~T();
      Z.~T();
    }

    // conversions
    operator VectorA<T, 2>() const
    {
      return XY;
    }

    // methods
    Dimension<3> Dimensions() const
    {
      return Dimension<3>();
    }

    // operators
    VectorA<T, 3> &operator-=(VectorA<T, 3> const &v)
    {
      X -= v.X;
      Y -= v.Y;
      Z -= v.Z;

      return (*this);
    }

    VectorA<T, 3> &operator+=(VectorA<T, 3> const &v)
    {
      X += v.X;
      Y += v.Y;
      Z += v.Z;

      return (*this);
    }

    VectorA<T, 3> &operator*=(T d)
    {
      X *= d;
      Y *= d;
      Z *= d;

      return (*this);
    }

    VectorA<T, 3> &operator*=(VectorA<T, 3> const &v)
    {
      X *= v.X;
      Y *= v.Y;
      Z *= v.Z;

      return (*this);
    }

    VectorA<T, 3> &operator/=(T d)
    {
      X /= d;
      Y /= d;
      Z /= d;

      return (*this);
    }

    VectorA<T, 3> &operator/=(VectorA<T, 3> const &v)
    {
      X /= v.X;
      Y /= v.Y;
      Z /= v.Z;

      return (*this);
    }

    VectorA<T, 3> &operator=(T d)
    {
      X = d;
      Y = d;
      Z = d;

      return (*this);
    }

    // do not need other = operators, since each vector type has the conversion operators
    VectorA<T, 3> &operator=(VectorA<T, 3> const &v)
    {
      if (this != &v) {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
      }

      return (*this);
    }

    friend VectorA<T, 3> operator-(VectorA<T, 3> v, T d)
    {
      v -= d;
      return v;
    }

    friend VectorA<T, 3> operator-(VectorA<T, 3> v, VectorA<T, 3> const &oV)
    {
      v -= oV;
      return v;
    }

    friend VectorA<T, 3> operator+(VectorA<T, 3> v, T d)
    {
      v += d;
      return v;
    }

    friend VectorA<T, 3> operator+(VectorA<T, 3> v, VectorA<T, 3> const &oV)
    {
      v += oV;
      return v;
    }

    friend VectorA<T, 3> operator*(VectorA<T, 3> v, T d)
    {
      v *= d;
      return v;
    }

    friend VectorA<T, 3> operator*(VectorA<T, 3> v, VectorA<T, 3> const &oV)
    {
      v *= oV;
      return v;
    }

    friend VectorA<T, 3> operator/(VectorA<T, 3> v, T d)
    {
      v /= d;
      return v;
    }

    friend VectorA<T, 3> operator/(VectorA<T, 3> v, VectorA<T, 3> const &oV)
    {
      v /= oV;
      return v;
    }

    bool operator==(VectorA<T, 3> const &v) const
    {
      return (X == v.X && Y == v.Y && Z == v.Z);
    }

    bool operator!=(VectorA<T, 3> const &v) const
    {
      return !(*this == v);
    }

    // add in other comparison operators

    T &operator[](int axis)
    {
      return XYZ[axis];
    }

    T operator[](int axis) const
    {
      return XYZ[axis];
    }
  };

  /*	TYPE DEFS	*/
  template<typename T>
  using Vector3 = VectorA<T, 3>;

  using Float3 = Vector3<float>;
  using Int3 = Vector3<int>;
  using Uint3 = Vector3<uint>;
}// namespace Math
}// namespace Core
