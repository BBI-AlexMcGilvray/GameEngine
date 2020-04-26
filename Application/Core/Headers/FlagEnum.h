#pragma once

#include "TemplateDefs.h"

namespace Core
{
	template <typename T>
	using IsEnum = typename EnableIf<std::is_enum<T>::value, int>::type;

	template <typename T, IsEnum<T> = 0>
	struct FlagEnum
	{
		T _baseEnum;

	public:
		FlagEnum(T baseEnum)
			: _baseEnum(baseEnum)
		{}

		bool AnyFlagSet()
		{
			return (int(_baseEnum) > 0);
		}

		bool AllFlagsSet(T flags)
		{
			return ((_baseEnum & flags) == _baseEnum);
		}
		
		bool AtLeastOneFlagSet(T flags)
		{
			return (int(_baseEnum & flags) > 0);
		}

		operator T() { return _baseEnum; }

		/*
		T operator &(const T other) { return (_baseEnum & (T)other); }
		T operator |(const T other) { return (_baseEnum | other); }
		T operator ^(const T other) { return (_baseEnum ^ other); }
		T operator ~() { return (~_baseEnum); }

		T& operator &=(const T other) { return (_baseEnum &= other); }
		T& operator |=(const T other) { return (_baseEnum |= other); }
		T& operator ^=(const T other) { return (_baseEnum |= other); }
		T& operator ~=(const T other) { return (_baseEnum |= other); }
		*/
	};

	template<class T, IsEnum<T> = 0>
	T operator ~(T a) { return (T)~(int)a; }
	template<class T, IsEnum<T> = 0>
	T operator |(T a, T b) { return (T)((int)a | (int)b); }
	template<class T, IsEnum<T> = 0>
	T operator &(T a, T b) { return (T)((int)a & (int)b); }
	template<class T, IsEnum<T> = 0>
	T operator ^(T a, T b) { return (T)((int)a ^ (int)b); }
	template<class T, IsEnum<T> = 0>
	T& operator |=(T& a, T b) { return (T&)((int&)a |= (int)b); }
	template<class T, IsEnum<T> = 0>
	T& operator &=(T& a, T b) { return (T&)((int&)a &= (int)b); }
	template<class T, IsEnum<T> = 0>
	T& operator ^=(T& a, T b) { return (T&)((int&)a ^= (int)b); }
}