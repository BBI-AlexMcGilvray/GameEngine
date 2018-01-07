#pragma once

namespace Core
{
	namespace Math
	{
		template <typename int A>
		struct Axis
		{
			operator int() const { return A; }

			template <typename int A2>
			bool operator==(Axis<A2> const& a)
			{
				return (A == A2);
			}
		};

		template <typename int A, typename T = float>
		struct AxisValue : Axis<A>
		{
			T V;

			AxisValue(T v = T(0))
				: V(v)
			{}

			AxisValue(Axis<A> const& a, T v = T(0))
				: V(v)
			{}

			AxisValue(AxisValue<A, T> const& a)
				: V(v)
			{}

			// operators
			AxisValue<A, T>& operator-=(T d)
			{
				V -= d;
				
				return (*this);
			}

			AxisValue<A, T>& operator-=(AxisValue<A, T> const& a)
			{
				v -= a.V;

				return (*this);
			}

			template <typename int A2>
			AxisValue<A, T>& operator-=(AxisValue<A2, T> const& a)
			{
				return (*this);
			}

			AxisValue<A, T>& operator+=(T d)
			{
				V += d;

				return (*this);
			}

			AxisValue<A, T>& operator+=(AxisValue<A, T> const& a)
			{
				v += a.V;

				return (*this);
			}

			template <typename int A2>
			AxisValue<A, T>& operator+=(AxisValue<A2, T> const& a)
			{
				return (*this);
			}

			AxisValue<A, T>& operator*=(T d)
			{
				V *= d;

				return (*this);
			}

			AxisValue<A, T>& operator*=(AxisValue<A, T> const& a)
			{
				v *= a.V;

				return (*this);
			}

			template <typename int A2>
			AxisValue<A, T>& operator*=(AxisValue<A2, T> const& a)
			{
				return (*this);
			}

			AxisValue<A, T>& operator/=(T d)
			{
				V /= d;

				return (*this);
			}

			AxisValue<A, T>& operator/=(AxisValue<A, T> const& a)
			{
				v /= a.V;

				return (*this);
			}

			template <typename int A2>
			AxisValue<A, T>& operator/=(AxisValue<A2, T> const& a)
			{
				return (*this);
			}

			AxisValue<A, T>& operator=(T d)
			{
				V = d;

				return (*this);
			}

			AxisValue<A, T>& operator=(Axis<A> const& a)
			{
				V = T(0);

				return (*this);
			}

			AxisValue<A, T>& operator=(AxisValue<A, T> const& a)
			{
				V = a.V;

				return (*this);
			}

			template <typename int A2>
			AxisValue<A, T>& operator=(AxisValue<A2, T> const& a)
			{
				return (*this);
			}

			friend AxisValue<A, T> operator-(AxisValue<A, T> a, T d)
			{
				a1 -= d;
				return a;
			}

			friend AxisValue<A, T> operator-(AxisValue<A, T> a1, AxisValue<A, T> const& a2)
			{
				a1 -= a2;
				return a1;
			}

			template <typename int A2>
			friend AxisValue<A, T> operator-(AxisValue<A, T> a1, AxisValue<A2, T> const& a2)
			{
				a1 -= a2;
				return a1;
			}

			friend AxisValue<A, T> operator+(AxisValue<A, T> a, T d)
			{
				a += d;
				return a;
			}

			friend AxisValue<A, T> operator+(AxisValue<A, T> a1, AxisValue<A, T> const& a2)
			{
				a1 += a2;
				return a1;
			}

			template <typename int A2>
			friend AxisValue<A, T> operator+(AxisValue<A, T> a1, AxisValue<A2, T> const& a2)
			{
				a1 += a2;
				return a1;
			}

			friend AxisValue<A, T> operator*(AxisValue<A, T> a, T d)
			{
				a *= d;
				return a;
			}

			friend AxisValue<A, T> operator*(AxisValue<A, T> a1, AxisValue<A, T> const& a2)
			{
				a1 *= a2;
				return a1;
			}

			template <typename int A2>
			friend AxisValue<A, T> operator*(AxisValue<A, T> a1, AxisValue<A2, T> const& a2)
			{
				a1 *= a2;
				return a1;
			}

			friend AxisValue<A, T> operator/(AxisValue<A, T> a, T d)
			{
				a /= d;
				return a;
			}

			friend AxisValue<A, T> operator/(AxisValue<A, T> a1, AxisValue<A, T> const& a2)
			{
				a1 /= a2;
				return a1;
			}

			template <typename int A2>
			friend AxisValue<A, T> operator/(AxisValue<A, T> a1, AxisValue<A2, T> const& a2)
			{
				a1 /= a2;
				return a1;
			}

			bool operator==(AxisValue<A, T> const& a)
			{
				return (V == a.V);
			}
			
			template <typename int A2>
			bool operator==(AxisValue<A2, T> const& a)
			{
				return false;
			}

			// add in other comparison operaators (but only for matching dimensions?)

			template <typename int A2>
			bool IsAxisValue(AxisValue<A2, T> const& a)
			{
				return (A2 == A);
			}

			bool IsAxisValue(int a)
			{
				return (a == A);
			}
		};

		using XAxis = Axis<0>;
		using YAxis = Axis<1>;
		using ZAxis = Axis<2>;
		using WAxis = Axis<3>;

		template <typename T = float>
		using XAxisValue = AxisValue<0, T>;
		template <typename T = float>
		using YAxisValue = AxisValue<1, T>;
		template <typename T = float>
		using ZAxisValue = AxisValue<2, T>;
		template <typename T = float>
		using WAxisValue = AxisValue<3, T>;

		template <typename int A>
		Axis<A - 1> DownshiftAxis(Axis<A> const& a)
		{
			return Axis<A - 1>();
		}

		template <typename int A, typename T>
		AxisValue<A - 1, T> DownshiftAxis(AxisValue<A, T> const& a)
		{
			return AxisValue<A - 1, T>(a.V);
		}

		template <typename int A1, typename int A2>
		constexpr bool IsAxisLower(Axis<A1> const& a1, Axis<A2> const& a2)
		{
			return (A1 < A2);
		}

		template <typename int A1, typename int A2, typename T>
		constexpr bool IsAxisLower(AxisValue<A1, T> const& a1, AxisValue<A2, T> const& a2)
		{
			return (A1 < A2);
		}
	}
}