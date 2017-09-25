#pragma once

#include "../../Debugging/Headers/Macros.h"

template <typename T>
T Lerp(T a, T b, float p)
{
	VERIFY(p >= 0.0f && p <= 1.0f);
	// initial + ((total possible difference) * percent)
	return (a + ((b - a) * p));
}

template <typename T>
T NLerp(T a, T b, float p)
{
	VERIFY(p >= 0.0f && p <= 1.0f);
	// initial + ((total possible difference) * percent)
	return Lerp(a, b, p).Normalize();
}

/*
template <typename T>
T Slerp(T a, T b, float p)
{
	do we need slerp? will be pretty heavy for maybe not enough gain
}
*/