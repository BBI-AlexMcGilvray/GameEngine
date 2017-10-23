#pragma once

#include <chrono>

namespace Core
{
	/*
		Much of the way this is set up is based on (obviously) wrapping the chrono library with guidance given by
		this talk by Howard Hinnant on chrono (https://www.youtube.com/watch?v=P32hvk8b13M)
	*/

	using SteadyClock = std::chrono::steady_clock; // steady clock to track time application has been open
	using Seconds = std::chrono::duration<float, std::milli>; // second based time duration, tracked as a float
	using TimePoint = std::chrono::time_point<SteadyClock, Seconds>; // individual time points based on the clock we are using

	constexpr Seconds operator ""_s(long double t) { return Seconds(t); }
	constexpr Seconds operator ""_s(unsigned long long int t) { return Seconds(t); }

	constexpr Seconds operator ""_m(long double t) { return Seconds(t * 60.0); }
	constexpr Seconds operator ""_m(unsigned long long int t) { return Seconds(t * 60); }

	constexpr Seconds operator ""_h(long double t) { return Seconds(t * 60.0_m); }
	constexpr Seconds operator ""_h(unsigned long long int t) { return Seconds(t * 60_m); }

	constexpr Seconds operator ""_d(long double t) { return Seconds(t * 24.0_h); }
	constexpr Seconds operator ""_d(unsigned long long int t) { return Seconds(t * 24_h); }
}