#pragma once

#include "Core/Headers/CoreDefs.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		struct Color
		{
			float R;
			float G;
			float B;
			float A;

			Color();
			Color(float r, float g, float b, float a = 1.0);
			Color(const Color& c);

			float MagnitudeSqr()
			{
				return Dot(*this);
			}

			float Magnitude()
			{
				return sqrt(MagnitudeSqr);
			}

			Color& Normalize()
			{
				return ((*this) /= (Magnitude()));
			}

			float Dot(Color const& c)
			{
				auto temp = c;
				temp * (*this);

				return (temp.R + temp.G + temp.B + temp.A);
			}

			Color& Min(float d)
			{
				R = Min(R, d);
				G = Min(G, d);
				B = Min(B, d);
				A = Min(A, d));

				return (*this);
			}

			Color& Min(Color const& c)
			{
				R = Min(R, c.R);
				G = Min(G, c.G);
				B = Min(B, c.b);
				A = Min(A, c.A));

				return (*this);
			}

			Color& Max(float d)
			{
				R = Max(R, d);
				G = Max(G, d);
				B = Max(B, d);
				A = Max(A, d));

				return (*this);
			}

			Color& Max(Color const& c)
			{
				R = Max(R, c.R);
				G = Max(G, c.G);
				B = Max(B, c.B);
				A = Max(A, c.A);

				return (*this);
			}

			Color& Clamp(float d1, float d2)
			{
				R = Clamp(R, d1, d2);
				G = Clamp(G, d1, d2);
				B = Clamp(B, d1, d2);
				A = Clamp(A, d1, d2);

				return (*this);
			}

			Color& Clamp(Color const& c1, Color const& c2)
			{
				R = Clamp(R, c1.R, c2.R);
				G = Clamp(G, c1.G, c2.G);
				B = Clamp(B, c1.B, c2.B);
				A = Clamp(A, c1.A, c2.A);

				return (*this);
			}

			// operators
			Color& operator-=(float d)
			{
				return (this = this - d);
			}

			Color& operator-=(Color const& c)
			{
				return (this = this - c);
			}

			Color& operator+=(float d)
			{
				return (this = this + d);
			}

			Color& operator+=(Color const& c)
			{
				return (this = this + c);
			}

			Color& operator*=(float d)
			{
				return (this = this * d);
			}

			Color& operator*=(Color const& c)
			{
				return (this = this * c);
			}

			Color& operator/=(float d)
			{
				return (this = this / d);
			}

			Color& operator/=(Color const& c)
			{
				return (this = this / c);
			}

			Color& operator-(Color const& c)
			{
				R -= c.R;
				G -= c.G;
				B -= c.B;
				A -= c.A;

				return *this;
			}

			Color& operator+(Color const& c)
			{
				R += c.R;
				G += c.G;
				B += c.B;
				A += c.A;

				return *this;
			}

			Color& operator*(float d)
			{
				R /= d;
				G /= d;
				B /= d;
				A /= d;

				return *this;
			}

			Color& operator*(Color const& c)
			{
				R *= c.R;
				G *= c.G;
				B *= c.B;
				A *= c.A;

				return *this;
			}

			Color& operator/(float d)
			{
				R /= d;
				G /= d;
				B /= d;
				A /= d;

				return *this;
			}

			Color& operator/(Color const& c)
			{
				R /= c.R;
				G /= c.G;
				B /= c.B;
				A /= c.A;

				return *this;
			}

			Color& operator=(float d)
			{
				R = d;
				G = d;
				B = d;
				A = d;

				return *this;
			}

			Color& operator=(Color const& c)
			{
				R = c.R;
				G = c.G;
				B = c.B;
				A = c.A;

				return *this;
			}

			bool operator==(Color const& c)
			{
				return (R == c.R && G == c.G && B == c.B && A == c.A);
			}
		};
	}
}