#pragma once

#include <array>

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/MathDefs.h"

namespace Core {
namespace Math {
  /*
		NOTES: (https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation)
			Quaternions, represented by (w, x, y, z), w + xi + yj + zk, or (w, u) - where u is a vector = (x, y, z),
			represent the ROTATION of ANGLE w AROUND THE AXIS (x, y, z) CLOCKWISE (assuming we are looking in the direction (x, y, z)

			Thus, when you multiply them by a vector (v), which is equivalent to a quaternion (0, v) (or: a rotation of NO ANGLE AROUND THE AXIS v,
			you are calculating the final result, which is a COMBINATION (initial state (0, v) being modified by state (w, u)) of rotations which
			results in a final state of (r, n) where n represents the axis v after it has been mapped through the transformation of (w, u).

			In other words, combining quaternion states gives us the final state, the vector part of which is the final axis - which represents the
			transformed vector part of the initial state. Which, in the case of direction, gives us our final direction after the initial direction
			was rotated by the quaternion

			Rotating a vector, v, by quaternion, q, gives us the equation v' = qvq' because one transformation (qv - first v then q) is equivalent
			to another transformation (v'q - first q then inverse of v), so we have v'q = qv which is equivalent to v' = qvq'
		*/

  template<typename T>
  struct Quaternion
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
              std::array<T, 2> XY;
            };
            T Z;
          };
          std::array<T, 3> XYZ;
        };
        T W;
      };
      std::array<T, 4> XYZW = {0};
    };

    Quaternion()
      : Quaternion(II())
    {}

    Quaternion(II i)
      : Quaternion(T(0), T(0), T(0), T(i))
    {}

    // would be nice if we could use Vector4<T> here, but it wouldn't compile
    Quaternion(T x, T y, T z, T w)
    {
      auto magnitude = sqrt((x * x) + (y * y) + (z * z) + (w * w));

      X = x / magnitude;
      Y = y / magnitude;
      Z = z / magnitude;
      W = w / magnitude;
    }

    Quaternion(Quaternion const &q)
      : X(q.X), Y(q.Y), Z(q.Z), W(q.W)
    {}

    // from euler angles
    Quaternion(Deg<T> x, Deg<T> y, Deg<T> z)
    {
      Rad<T> rx(x);
      Rad<T> ry(y);
      Rad<T> rz(z);

      T cosX = cos(rx / T(2));
      T sinX = sin(rx / T(2));

      T cosY = cos(ry / T(2));
      T sinY = sin(ry / T(2));

      T cosZ = cos(rz / T(2));
      T sinZ = sin(rz / T(2));

      W = (cosX * cosY * cosZ) + (sinX * sinY * sinZ);
      X = (sinX * cosY * cosZ) - (cosX * sinY * sinZ);
      Y = (cosX * sinY * cosZ) + (sinX * cosY * sinZ);
      Z = (cosX * cosY * sinZ) - (sinX * sinY * cosZ);
    }

    template<int A>
    Quaternion(const Deg<T> &deg, const Axis<A> &axis)
      : Quaternion((axis == XAxis()) ? deg : T(0), (axis == YAxis()) ? deg : T(0), (axis == ZAxis()) ? deg : T(0))
    {}

    Quaternion<T> Inverse() const
    {
      T qMagnitudeSqr = (X * X) + (Y * Y) + (Z * Z) + (W * W);

      return Conjugate() / qMagnitudeSqr;
    }

    Quaternion<T> Conjugate() const
    {
      return Quaternion<T>(-X, -Y, -Z, W);
    }

    // operators
    Quaternion<T> &operator-=(Quaternion<T> const &q)
    {
      MESSAGE(false, "Don't use this - why are you using this?");

      return (*this);
    }

    Quaternion<T> &operator+=(Quaternion<T> const &q)
    {
      MESSAGE(false, "Don't use this - why are you using this?");

      return (*this);
    }

    Quaternion<T> &operator*=(Quaternion<T> const &q)
    {
      T newW = (W * q.W) - (X * q.X) - (Y * q.Y) - (Z * q.Z);
      T newX = (W * q.X) + (X * q.W) + (Y * q.Z) - (Z * q.Y);
      T newY = (W * q.Y) - (X * q.Z) + (Y * q.W) + (Z * q.X);
      T newZ = (W * q.Z) + (X * q.Y) - (Y * q.X) + (Z * q.W);

      X = newX;
      Y = newY;
      Z = newZ;
      W = newW;

      return (*this);
    }

    Quaternion<T> &operator/=(T d)
    {
      X /= d;
      Y /= d;
      Z /= d;
      W /= d;
      return (*this);
    }

    Quaternion<T> &operator/=(Quaternion<T> const &q)
    {
      Quaternion<T> qInverse = q.Inverse();
      qInverse *= (*this);

      X = qInverse.X;
      Y = qInverse.Y;
      Z = qInverse.Z;
      W = qInverse.W;

      return (*this);
    }

    Quaternion<T> &operator=(Quaternion<T> const &q)
    {
      X = q.X;
      Y = q.Y;
      Z = q.Z;
      W = q.W;

      return *this;
    }

    friend Quaternion<T> operator-(Quaternion<T> q, Quaternion<T> const &oQ)
    {
      MESSAGE(false, "Don't use this - why are you using this?");

      return q;
    }

    friend Quaternion<T> operator+(Quaternion<T> q, Quaternion<T> const &oQ)
    {
      MESSAGE(false, "Don't use this - why are you using this?");

      return q;
    }

    friend Quaternion<T> operator*(Quaternion<T> q, Quaternion<T> const &oQ)
    {
      q *= oQ;
      return q;
    }

    friend Quaternion<T> operator/(Quaternion<T> q, T d)
    {
      q /= d;
      return q;
    }

    friend Quaternion<T> operator/(Quaternion<T> q, Quaternion<T> const &oQ)
    {
      q /= oQ;
      return q;
    }

    bool operator==(Quaternion<T> const &q) const
    {
      return (X == q.X && Y == q.Y && Z == q.Z && W == q.W);
    }

    bool operator!=(Quaternion<T> const& q) const
    {
      return !(*this == q);
    }

    // other comparison operators have no meaning

    T &operator[](int index)
    {
      return XYZW[index];
    }

    T operator[](int index) const
    {
      return XYZW[index];
    }
  };

  /*	TYPE DEFS	*/
  using FQuaternion = Quaternion<float>;
}// namespace Math
}// namespace Core