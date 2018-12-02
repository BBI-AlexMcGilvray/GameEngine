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
	
	template <typename T1, typename T2>
	auto Min(T1&& a, T2&& b) { return ((Forward<T1>(a) < Forward<T2>(b)) ? Forward<T1>(a) : Forward<T2>(b)); }
	template <typename T1, typename T2>
	auto Max(T1&& a, T2&& b) { return ((Forward<T1>(a) > Forward<T2>(b)) ? Forward<T1>(a) : Forward<T2>(b)); }
	template <typename T1, typename T2, typename T3>
	auto Clamp(T1&& a, T2&& min, T3&& max) { return (Max(Min(Forward<T1>(a), Forward<T3>(max)), Forward<T2>(min))); }
	template <typename T1, typename T2, typename T3>
	bool Within(T1&& d, T2&& v, T3&& var) { return ((Forward<T1>(d) >= Forward<T2>(v) - Forward<T3>(var)) && (Forward<T1>(d) <= Forward<T2>(v) + Forward<T3>(var))); }
	template <typename T1, typename T2, typename T3>
	bool InRange(T1&& var, T2&& min, T3&& max) { return ((Forward<T1>(var) >= Forward<T2>(min)) && (Forward<T1>(var) <= Forward<T3>(max))); }
	
	using uint = unsigned int;
	using size = size_t;
}