#pragma once

#include <string>
#include <utility>

namespace Core
{
	using String = std::string;

	template <typename T>
	String ToString(T&& v) { return std::to_string(Forward<T>(v)); }

	template <typename T1, typename T2 = T1>
	using Pair = std::pair<T1, T2>;

	template <typename T>
	struct Truth
	{
		bool Result;
		T Value;

		Truth(bool result, T value)
			: Result(result), Value(value)
		{}

		operator bool()
		{
			return Result;
		}

		operator T && ()
		{
			return Value;
		}
	};
	
	template <typename T>
	T&& Min(T&& a, T&& b) { return ((Forward<T>(a) < Forward<T>(b)) ? Forward<T>(a) : Forward<T>(b)); }
	template <typename T>
	T&& Max(T&& a, T&& b) { return ((Forward<T>(a) > Forward<T>(b)) ? Forward<T>(a) : Forward<T>(b)); }
	template <typename T>
	T&& Clamp(T&& a, T&& min, T&& max) { return (Max(Min(Forward<T>(a), Forward<T>(max)), Forward<T>(min))); }
	template <typename T>
	bool Within(T&& d, T&& v, T&& var) { return ((Forward<T>(d) >= Forward<T>(v) - Forward<T>(var)) && (Forward<T>(d) <= Forward<T>(v) + Forward<T>(var))); }
	
	using uint = unsigned int;
}