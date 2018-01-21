#pragma once

#include <chrono>

namespace Core
{
	/*
		Much of the way this is set up is based on (obviously) wrapping the chrono library with guidance given by
		this talk by Howard Hinnant on chrono (https://www.youtube.com/watch?v=P32hvk8b13M)
	*/

	using SteadyClock = std::chrono::steady_clock; // steady clock to track time application has been open
	using Second = std::chrono::duration<float, std::milli>; // second based time duration, tracked as a float
	using TimePoint = std::chrono::time_point<SteadyClock, Second>; // individual time points based on the clock we are using

	constexpr Second operator ""_ms(long double t) { return Second(t / 1000.0); }
	constexpr Second operator ""_ms(unsigned long long int t) { return Second(t / 1000); }

	constexpr Second operator ""_s(long double t) { return Second(t); }
	constexpr Second operator ""_s(unsigned long long int t) { return Second(t); }

	constexpr Second operator ""_min(long double t) { return Second(t * 60.0_s); }
	constexpr Second operator ""_min(unsigned long long int t) { return Second(t * 60_s); }

	constexpr Second operator ""_h(long double t) { return Second(t * 60.0_min); }
	constexpr Second operator ""_h(unsigned long long int t) { return Second(t * 60_min); }

	constexpr Second operator ""_d(long double t) { return Second(t * 24.0_h); }
	constexpr Second operator ""_d(unsigned long long int t) { return Second(t * 24_h); }

	// helper functions

	template <typename T, typename R>
	T Duration(std::chrono::duration<T, R> duration)
	{
		// amount, divided by the ratio (detail tracked)
		return (T(duration.count()) / T(R::den));
	}
}