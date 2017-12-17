#pragma once

#include "Core/Headers/CoreDefs.h"

#include "MathDefs.h"
#include "MathUtils.h"

#include "Vector.h"

namespace Core
{
	namespace Math
	{
		struct Color : VectorA<float, 4>
		{
			union
			{
				struct
				{
					float R;
					float G;
					float B;
					float A;
				};
				float Values[4];
			};

			Color()
				: Color(II())
			{}

			Color(II i)
				: R(i), G(i), B(i), A(i)
			{}

			Color(float d)
				: R(d), G(d), B(d), A(d)
			{}

			Color(float r, float g, float b, float a = 1.0)
				: R(r), G(g), B(b), A(a)
			{}

			Color(const Color& c)
				: R(c.R), B(c.B), G(c.G), A(c.A)
			{}

			// operators
			// methods
			Dimension<4> Dimensions()
			{
				return Dimension<4>();
			}

			// operators
			Color& operator-=(float d)
			{
				R -= d;
				G -= d;
				B -= d;
				A -= d;

				return (*this);
			}

			Color& operator-=(Color const& c)
			{
				R -= c.R;
				G -= c.G;
				B -= c.B;
				A -= c.A;

				return (*this);
			}

			Color& operator+=(float d)
			{
				R += d;
				G += d;
				B += d;
				A += d;

				return (*this);
			}

			Color& operator+=(Color const& c)
			{
				R += c.R;
				G += c.G;
				B += c.B;
				A += c.A;

				return (*this);
			}

			Color& operator*=(float d)
			{
				R *= d;
				G *= d;
				B *= d;
				A *= d;

				return (*this);
			}

			Color& operator*=(Color const& c)
			{
				R *= c.R;
				G *= c.G;
				B *= c.B;
				A *= c.A;

				return (*this);
			}

			Color& operator/=(float d)
			{
				R /= d;
				G /= d;
				B /= d;
				A /= d;

				return (*this);
			}

			Color& operator/=(Color const& c)
			{
				R /= c.R;
				G /= c.G;
				B /= c.B;
				A /= c.A;

				return (*this);
			}

			Color& operator=(float d)
			{
				R = d;
				G = d;
				B = d;
				A = d;

				return (*this);
			}

			Color& operator=(Color const& c)
			{
				if (this != &c)
				{
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

			friend Color operator-(Color c, Color const& oC)
			{
				c -= oC;
				return c;
			}

			friend Color operator+(Color c, float d)
			{
				c += d;
				return c;
			}

			friend Color operator+(Color c, Color const& oC)
			{
				c += oC;
				return c;
			}

			friend Color operator*(Color c, float d)
			{
				c *= d;
				return c;
			}

			friend Color operator*(Color c, Color const& oC)
			{
				c *= oC;
				return c;
			}

			friend Color operator/(Color c, float d)
			{
				c /= d;
				return c;
			}

			friend Color operator/(Color c, Color const& oC)
			{
				c /= oC;
				return c;
			}

			bool operator==(Color const& c)
			{
				return (R == c.R && G == c.G && B == c.B && A == c.A);
			}

			float& operator[](int axis)
			{
				return Values[axis];
			}

			float operator[](int axis) const
			{
				return Values[axis];
			}
		};
	}
}