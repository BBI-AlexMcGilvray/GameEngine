#pragma once

#include <array>

#include "Core/Math/Headers/Vector3.h"

namespace Core {
namespace Math {
  template<typename T>
  struct VectorA<T, 4>
  {
    union {
      struct
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
          Vector3<T> XYZ;
        };
        T W;
      };
      std::array<T, 4> XYZW;
    };

    VectorA()
    {}

    VectorA(const T &d)
      : X(d), Y(d), Z(d), W(d)
    {}

    VectorA(const T &x, const T &y, const T &z, const T &w)
      : X(x), Y(y), Z(z), W(w)
    {}

    VectorA(VectorA<T, 2> const &v, const T &d1 = 0, const T &d2 = 0)
      : XY(v), Z(d1), W(d2)
    {}

    VectorA(VectorA<T, 3> const &v, const T &d = 0)
      : XYZ(v), W(d)
    {}

    VectorA(VectorA<T, 4> const &v)
      : X(v.X), Y(v.Y), Z(v.Z), W(v.W)
    {}

    ~VectorA()
    {
      X.~T();
      Y.~T();
      Z.~T();
      W.~T();
    }

    // conversions
    operator VectorA<T, 2>() const
    {
      return XY;
    }

    operator VectorA<T, 3>() const
    {
      return XYZ;
    }

    // methods
    Dimension<4> Dimensions() const
    {
      return Dimension<4>();
    }

    // operators
    VectorA<T, 4> &operator-=(VectorA<T, 4> const &v)
    {
      X -= v.X;
      Y -= v.Y;
      Z -= v.Z;
      W -= v.W;

      return (*this);
    }

    VectorA<T, 4> &operator+=(VectorA<T, 4> const &v)
    {
      X += v.X;
      Y += v.Y;
      Z += v.Z;
      W += v.w;

      return (*this);
    }

    VectorA<T, 4> &operator*=(T d)
    {
      X *= d;
      Y *= d;
      Z *= d;
      W *= d;

      return (*this);
    }

    VectorA<T, 4> &operator*=(VectorA<T, 4> const &v)
    {
      X *= v.X;
      Y *= v.Y;
      Z *= v.Z;
      W *= v.W;

      return (*this);
    }

    VectorA<T, 4> &operator/=(T d)
    {
      X /= d;
      Y /= d;
      Z /= d;
      W /= d;

      return (*this);
    }

    VectorA<T, 4> &operator/=(VectorA<T, 4> const &v)
    {
      X /= v.X;
      Y /= v.Y;
      Z /= v.Z;
      W /= v.W;

      return (*this);
    }

    VectorA<T, 4> &operator=(T d)
    {
      X = d;
      Y = d;
      Z = d;
      W = d;

      return (*this);
    }

    // do not need other = operators, since each vector type has the conversion operators
    VectorA<T, 4> &operator=(VectorA<T, 4> const &v)
    {
      if (this != &v) {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
        W = v.W;
      }

      return (*this);
    }

    friend VectorA<T, 4> operator-(VectorA<T, 4> v, T d)
    {
      v -= d;
      return v;
    }

    friend VectorA<T, 4> operator-(VectorA<T, 4> v, VectorA<T, 4> const &oV)
    {
      v -= oV;
      return v;
    }

    friend VectorA<T, 4> operator+(VectorA<T, 4> v, T d)
    {
      v += d;
      return v;
    }

    friend VectorA<T, 4> operator+(VectorA<T, 4> v, VectorA<T, 4> const &oV)
    {
      v += oV;
      return v;
    }

    friend VectorA<T, 4> operator*(VectorA<T, 4> v, T d)
    {
      v *= d;
      return v;
    }

    friend VectorA<T, 4> operator*(VectorA<T, 4> v, VectorA<T, 4> const &oV)
    {
      v *= oV;
      return v;
    }

    friend VectorA<T, 4> operator/(VectorA<T, 4> v, T d)
    {
      v /= d;
      return v;
    }

    friend VectorA<T, 4> operator/(VectorA<T, 4> v, VectorA<T, 4> const &oV)
    {
      v /= oV;
      return v;
    }

    bool operator==(VectorA<T, 4> const &v) const
    {
      return (X == v.X && Y == v.Y && Z == v.Z && W == v.W);
    }

    bool operator!=(VectorA<T, 4> const &v) const
    {
      return !(*this == v);
    }

    // add in other comparison operators

    T &operator[](int axis)
    {
      return XYZW[axis];
    }

    T operator[](int axis) const
    {
      return XYZW[axis];
    }
  };

  /*	TYPE DEFS	*/
  template<typename T>
  using Vector4 = VectorA<T, 4>;

  using Float4 = Vector4<float>;
  using Int4 = Vector4<int>;
  using Uint4 = Vector4<uint>;
}// namespace Math
}// namespace Core
