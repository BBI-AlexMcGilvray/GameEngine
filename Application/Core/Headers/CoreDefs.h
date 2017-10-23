#pragma once

#include <string>
#include <utility>

namespace Core
{
	using String = std::string;

	template <typename T>
	String ToString(T v) { return std::to_string(v); }

	template <typename T1, typename T2 = T1>
	using Pair = std::pair<T1, T2>;
	
	template <typename T>
	T Min(T a, T b) { return ((a < b) ? a : b); }
	template <typename T>
	T Max(T a, T b) { return ((a > b) ? a : b); }
	template <typename T>
	T Clamp(T a, T min, T max) { return (Max(Min(a, max), min)); }
	template <typename T>
	bool Within(T d, T v, T var) { return ((d >= v - var) && (d <= v + var)); }
	
	using uint = unsigned int;
}