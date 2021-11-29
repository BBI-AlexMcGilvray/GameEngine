#pragma once

#include <array>

#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/MathDefs.h"
#include "Core/Math/Headers/MathUtils.h"

namespace Core {
namespace Math {
  struct Color
  {
    union {
      struct
      {
        union {
          struct {
              float R;
              float G;
              float B;
          };
          std::array<float, 3> RGB;
        };
        float A;
      };
      std::array<float, 4> RGBA;
    };

    constexpr Color()
      : Color(II())
    {}

    constexpr Color(II i)
      : R(i), G(i), B(i), A(i)
    {}

    constexpr Color(float d)
      : R(d), G(d), B(d), A(d)
    {}

    constexpr Color(float r, float g, float b, float a = 1.0)
      : R(r), G(g), B(b), A(a)
    {}

    constexpr Color(const Color &c)
      : R(c.R), B(c.B), G(c.G), A(c.A)
    {}

    // operators
    // methods
    Dimension<4> Dimensions() const
    {
      return Dimension<4>();
    }

    // operators
    Color &operator-=(float d)
    {
      R -= d;
      G -= d;
      B -= d;
      A -= d;

      return (*this);
    }

    Color &operator-=(Color const &c)
    {
      R -= c.R;
      G -= c.G;
      B -= c.B;
      A -= c.A;

      return (*this);
    }

    Color &operator+=(float d)
    {
      R += d;
      G += d;
      B += d;
      A += d;

      return (*this);
    }

    Color &operator+=(Color const &c)
    {
      R += c.R;
      G += c.G;
      B += c.B;
      A += c.A;

      return (*this);
    }

    Color &operator*=(float d)
    {
      R *= d;
      G *= d;
      B *= d;
      A *= d;

      return (*this);
    }

    Color &operator*=(Color const &c)
    {
      R *= c.R;
      G *= c.G;
      B *= c.B;
      A *= c.A;

      return (*this);
    }

    Color &operator/=(float d)
    {
      R /= d;
      G /= d;
      B /= d;
      A /= d;

      return (*this);
    }

    Color &operator/=(Color const &c)
    {
      R /= c.R;
      G /= c.G;
      B /= c.B;
      A /= c.A;

      return (*this);
    }

    Color &operator=(float d)
    {
      R = d;
      G = d;
      B = d;
      A = d;

      return (*this);
    }

    Color &operator=(Color const &c)
    {
      if (this != &c) {
        R = c.R;
        G = c.G;
        B = c.B;
        A = c.A;
      }

      return (*this);
    }

    friend Color operator-(Color c, float d)
    {
      c -= d;
      return c;
    }

    friend Color operator-(Color c, Color const &oC)
    {
      c -= oC;
      return c;
    }

    friend Color operator+(Color c, float d)
    {
      c += d;
      return c;
    }

    friend Color operator+(Color c, Color const &oC)
    {
      c += oC;
      return c;
    }

    friend Color operator*(Color c, float d)
    {
      c *= d;
      return c;
    }

    friend Color operator*(Color c, Color const &oC)
    {
      c *= oC;
      return c;
    }

    friend Color operator/(Color c, float d)
    {
      c /= d;
      return c;
    }

    friend Color operator/(Color c, Color const &oC)
    {
      c /= oC;
      return c;
    }

    bool operator==(const Color &c) const
    {
      return (R == c.R && G == c.G && B == c.B && A == c.A);
    }

    bool operator!=(const Color& c) const
    {
      return !(*this == c);
    }

    float &operator[](int axis)
    {
      return RGBA[axis];
    }

    float operator[](int axis) const
    {
      return RGBA[axis];
    }
  };

  constexpr Color WHITE = Color(1.0f, 1.0f, 1.0f, 1.0f);
  constexpr Color BLACK = Color(0.0f, 0.0f, 0.0f, 1.0f);
  constexpr Color RED = Color(1.0f, 0.0f, 0.0f, 1.0f);
  constexpr Color GREEN = Color(0.0f, 1.0f, 0.0f, 1.0f);
  constexpr Color BLUE = Color(0.0f, 0.0f, 1.0f, 1.0f);
}// namespace Math
}// namespace Core