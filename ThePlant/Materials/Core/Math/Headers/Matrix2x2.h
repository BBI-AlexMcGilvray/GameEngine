#pragma once

#include <array>
#include <utility>

#include "Core/Math/Headers/Matrix.h"
#include "Core/Math/Headers/Vector2.h"

namespace Core {
namespace Math {
  /*
			Our matrices are column - major, NOT row - major.
		*/
  template<typename T>
  struct MatrixAxB<T, 2, 2>
  {
    union {
      struct
      {
        Vector2<T> E1;
        Vector2<T> E2;
      };
      std::array<Vector2<T>, 2> E1E2;
    };

    // constructors
    MatrixAxB()
      : MatrixAxB(II())
    {}

    MatrixAxB(MatrixAxB<T, 2, 2> const &m)
      : E1(m.E1), E2(m.E2)
    {}

    MatrixAxB(VectorA<T, 2> const &e1, VectorA<T, 2> const &e2)
      : E1(e1), E2(e2)
    {}

    MatrixAxB(const II& i)
      : E1(T(i), T(0)), E2(T(0), T(i))
    {}

    MatrixAxB(const T& d)
      : E1(d), E2(d)
    {}

    MatrixAxB(const T& d1, const T& d2, const T& d3 = 0, const T& d4 = 0)
      : E1(d1, d2), E2(d3, d4)
    {}

    ~MatrixAxB()
    {
      E1.~VectorA<T, 2>();
      E2.~VectorA<T, 2>();
    }

    // conversions
    operator MatrixAxB<T, 3, 3>() const
    {
      return MatrixAxB<T, 3, 3>(E1, E2, T(0));
    }

    operator MatrixAxB<T, 4, 4>() const
    {
      return MatrixAxB<T, 4, 4>(E1, E2, T(0), T(0));
    }

    // methods
    std::pair<Dimension<2>, Dimension<2>> Dimensions() const
    {
      return std::pair<Dimension<2>, Dimension<2>>(2, 2);
    }

    void SetColumn(const int& column, const VectorA<T, 2>& columnVector)
    {
      (*this)[column] = columnVector;
    }

    VectorA<T, 2> GetColumn(const int& column) const
    {
      return (*this)[column];
    }

    VectorA<T, 2>& GetColumn(const int& column)
    {
      return (*this)[column];
    }

    void SetRow(const int& row, const VectorA<T, 2>& rowVector)
    {
      for (int i = 0; i < 2; i++) {
        (*this)[i][row] = rowVector[i];
      }
    }

    VectorA<T, 2> GetRow(const int& row) const
    {
      VectorA<T, 2> rowV;
      for (int i = 0; i < 2; i++) {
        rowV[i] = (*this)[i][row];
      }

      return rowV;
    }

    // operators
    MatrixAxB<T, 2, 2> &operator-=(const MatrixAxB<T, 2, 2>& m)
    {
      E1 -= m.E1;
      E2 -= m.E2;

      return *this;
    }

    MatrixAxB<T, 2, 2> &operator+=(const MatrixAxB<T, 2, 2>& m)
    {
      E1 += m.E1;
      E2 += m.E2;

      return *this;
    }

    MatrixAxB<T, 2, 2> &operator*=(const T& d)
    {
      E1 *= d;
      E2 *= d;

      return *this;
    }

    MatrixAxB<T, 2, 2> &operator*=(const MatrixAxB<T, 2, 2> &m)
    {
      auto newCol1 = VectorA<T, 2>(Dot((*this).GetRow(0), m.E1), Dot((*this).GetRow(0), m.E2));
      auto newCol2 = VectorA<T, 2>(Dot((*this).GetRow(1), m.E1), Dot((*this).GetRow(1), m.E2));

      E1 = VectorA<T, 2>(newCol1.X, newCol2.X);
      E2 = VectorA<T, 2>(newCol1.Y, newCol2.Y);

      return *this;
    }

    MatrixAxB<T, 2, 2> &operator/=(const T& d)
    {
      E1 /= d;
      E2 /= d;

      return *this;
    }

    MatrixAxB<T, 2, 2> &operator/=(const MatrixAxB<T, 2, 2> &m)
    {
      E1 /= m.E1;
      E2 /= m.E2;

      return *this;
    }

    MatrixAxB<T, 2, 2> &operator=(const T& d)
    {
      E1 = VectorA<T, 4>(d);
      E2 = VectorA<T, 4>(d);

      return *this;
    }

    MatrixAxB<T, 2, 2> &operator=(const MatrixAxB<T, 2, 2> &m)
    {
      E1 = m.E1;
      E2 = m.E2;

      return *this;
    }

    friend MatrixAxB<T, 2, 2> operator-(MatrixAxB<T, 2, 2>& m, const T& d)
    {
      m -= d;
      return m;
    }

    friend MatrixAxB<T, 2, 2> operator-(MatrixAxB<T, 2, 2> m, const MatrixAxB<T, 2, 2> &oM)
    {
      m -= oM;
      return m;
    }

    friend MatrixAxB<T, 2, 2> operator+(MatrixAxB<T, 2, 2> m, const T& d)
    {
      m += d;
      return m;
    }

    friend MatrixAxB<T, 2, 2> operator+(MatrixAxB<T, 2, 2> m, const MatrixAxB<T, 2, 2> &oM)
    {
      m += oM;
      return m;
    }

    friend MatrixAxB<T, 2, 2> operator*(MatrixAxB<T, 2, 2> m, const T& d)
    {
      m *= d;
      return m;
    }

    friend MatrixAxB<T, 2, 2> operator*(MatrixAxB<T, 2, 2> m, const MatrixAxB<T, 2, 2> &oM)
    {
      m *= oM;
      return m;
    }

    friend VectorA<T, 2> operator*(MatrixAxB<T, 2, 2> m, const VectorA<T, 2> &v)
    {
      VectorA<T, 2> nV(Dotr(m.GetRow(0), v), Dot(m.GetRow(1), v));

      return nV;
    }

    friend MatrixAxB<T, 2, 2> operator/(MatrixAxB<T, 2, 2> m, const T& d)
    {
      m /= d;
      return m;
    }

    friend MatrixAxB<T, 2, 2> operator/(MatrixAxB<T, 2, 2> m, const MatrixAxB<T, 2, 2> &oM)
    {
      m /= oM;
      return m;
    }

    bool operator==(const MatrixAxB<T, 2, 2> &m) const
    {
      return (E1 == m.E1 && E2 == m.E2);
    }

    bool operator!=(const MatrixAxB<T, 2, 2>& m) const
    {
      return !(*this == m);
    }

    // other comparison operators have no meaning

    VectorA<T, 2> &operator[](int basis)
    {
      return E1E2[basis];
    }

    VectorA<T, 2> operator[](int basis) const
    {
      return E1E2[basis];
    }
  };

  /*	TYPE DEFS	*/
  template<typename T>
  using Matrix2x2 = MatrixAxB<T, 2, 2>;

  using Float2x2 = Matrix2x2<float>;
  using Int2x2 = Matrix2x2<int>;
  using Uint2x2 = Matrix2x2<uint>;
}// namespace Math
}// namespace Core