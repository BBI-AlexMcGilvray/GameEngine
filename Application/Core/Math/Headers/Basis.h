#pragma once

#include <cmath>

namespace Core
{
	namespace Math
	{
		template <typename int A>
		struct Basis
		{
			operator int() const { return A; }

			template <typename int A2>
			bool operator==(Basis<A2> const& b)
			{
				return (A == A2);
			}
		};

		template <typename int A, typename T = float>
		struct BasisValue : Basis<A>
		{
			T V;

			BasisValue(T v = T(0))
				: V(v)
			{}

			BasisValue(Basis<A> const& a, T v = T(0))
				: V(v)
			{}

			BasisValue(BasisValue<A, T> const& a)
				: V(v)
			{}

			// operators
			BasisValue<A, T>& operator-=(T d)
			{
				V -= d;

				return (*this);
			}

			BasisValue<A, T>& operator-=(BasisValue<A, T> const& a)
			{
				v -= a.V;

				return (*this);
			}

			template <typename int A2>
			BasisValue<A, T>& operator-=(BasisValue<A2, T> const& a)
			{
				return (*this);
			}

			BasisValue<A, T>& operator+=(T d)
			{
				V += d;

				return (*this);
			}

			BasisValue<A, T>& operator+=(BasisValue<A, T> const& a)
			{
				v += a.V;

				return (*this);
			}

			template <typename int A2>
			BasisValue<A, T>& operator+=(BasisValue<A2, T> const& a)
			{
				return (*this);
			}

			BasisValue<A, T>& operator*=(T d)
			{
				V *= d;

				return (*this);
			}

			BasisValue<A, T>& operator*=(BasisValue<A, T> const& a)
			{
				v *= a.V;

				return (*this);
			}

			template <typename int A2>
			BasisValue<A, T>& operator*=(BasisValue<A2, T> const& a)
			{
				return (*this);
			}

			BasisValue<A, T>& operator/=(T d)
			{
				V /= d;

				return (*this);
			}

			BasisValue<A, T>& operator/=(BasisValue<A, T> const& a)
			{
				v /= a.V;

				return (*this);
			}

			template <typename int A2>
			BasisValue<A, T>& operator/=(BasisValue<A2, T> const& a)
			{
				return (*this);
			}

			BasisValue<A, T>& operator=(T d)
			{
				V = d;

				return (*this);
			}

			BasisValue<A, T>& operator=(Basis<A> const& a)
			{
				V = T(0);

				return (*this);
			}

			BasisValue<A, T>& operator=(BasisValue<A, T> const& a)
			{
				V = a.V;

				return (*this);
			}

			template <typename int A2>
			BasisValue<A, T>& operator=(BasisValue<A2, T> const& a)
			{
				return (*this);
			}

			friend BasisValue<A, T> operator-(BasisValue<A, T> a, T d)
			{
				a1 -= d;
				return a;
			}

			friend BasisValue<A, T> operator-(BasisValue<A, T> a1, BasisValue<A, T> const& a2)
			{
				a1 -= a2;
				return a1;
			}

			template <typename int A2>
			friend BasisValue<A, T> operator-(BasisValue<A, T> a1, BasisValue<A2, T> const& a2)
			{
				a1 -= a2;
				return a1;
			}

			friend BasisValue<A, T> operator+(BasisValue<A, T> a, T d)
			{
				a += d;
				return a;
			}

			friend BasisValue<A, T> operator+(BasisValue<A, T> a1, BasisValue<A, T> const& a2)
			{
				a1 += a2;
				return a1;
			}

			template <typename int A2>
			friend BasisValue<A, T> operator+(BasisValue<A, T> a1, BasisValue<A2, T> const& a2)
			{
				a1 += a2;
				return a1;
			}

			friend BasisValue<A, T> operator*(BasisValue<A, T> a, T d)
			{
				a *= d;
				return a;
			}

			friend BasisValue<A, T> operator*(BasisValue<A, T> a1, BasisValue<A, T> const& a2)
			{
				a1 *= a2;
				return a1;
			}

			template <typename int A2>
			friend BasisValue<A, T> operator*(BasisValue<A, T> a1, BasisValue<A2, T> const& a2)
			{
				a1 *= a2;
				return a1;
			}

			friend BasisValue<A, T> operator/(BasisValue<A, T> a, T d)
			{
				a /= d;
				return a;
			}

			friend BasisValue<A, T> operator/(BasisValue<A, T> a1, BasisValue<A, T> const& a2)
			{
				a1 /= a2;
				return a1;
			}

			template <typename int A2>
			friend BasisValue<A, T> operator/(BasisValue<A, T> a1, BasisValue<A2, T> const& a2)
			{
				a1 /= a2;
				return a1;
			}

			bool operator==(BasisValue<A, T> const& a)
			{
				return (V == a.V);
			}

			template <typename int A2>
			bool operator==(BasisValue<A2, T> const& a)
			{
				return false;
			}

			// add in other comparison operaators (but only for matching dimensions?)

			template <typename int A2>
			bool IsBasisValue(BasisValue<A2, T> const& a)
			{
				return (A2 == A);
			}

			bool IsBasisValue(int a)
			{
				return (a == A);
			}
		};

		using Basis0 = Basis<0>;
		using Basis1 = Basis<1>;
		using Basis2 = Basis<2>;
		using Basis3 = Basis<3>;

		template <typename T = float>
		using Basis0Value = BasisValue<0, T>;
		template <typename T = float>
		using Basis1Value = BasisValue<1, T>;
		template <typename T = float>
		using Basis2Value = BasisValue<2, T>;
		template <typename T = float>
		using Basis3Value = BasisValue<3, T>;

		template <typename int A>
		Basis<A - 1> DownshiftBasis(Basis<A> const& a)
		{
			return Basis<A - 1>();
		}

		template <typename int A, typename T>
		BasisValue<A - 1, T> DownshiftBasis(BasisValue<A, T> const& a)
		{
			return BasisValue<A - 1, T>(a.V);
		}

		template <typename int A1, typename int A2>
		constexpr bool IsBasisLower(Basis<A1> const& a1, Basis<A2> const& a2)
		{
			return (A1 < A2);
		}

		template <typename int A1, typename int A2, typename T>
		constexpr bool IsBasisLower(BasisValue<A1, T> const& a1, BasisValue<A2, T> const& a2)
		{
			return (A1 < A2);
		}
	}
}