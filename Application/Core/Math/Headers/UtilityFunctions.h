#pragma once

#include "Core/Debugging/Headers/Macros.h"

#include "QuaternionFunctions.h"
#include "VectorFunctions.h"

namespace Core
{
	namespace Math
	{
		template <typename T>
		T Lerp(T a, T b, float p)
		{
			// initial + ((total possible difference) * percent)
			return (a + ((b - a) * p));
		}

		FQuaternion LerpQuat(FQuaternion a, FQuaternion b, float p);

		template <typename T>
		T NLerp(T a, T b, float p)
		{
			// Normalized Lerp
			return Normalize(Lerp(a, b, p));
		}

		/*
		template <typename T>
		T Slerp(T a, T b, float p)
		{
			do we need slerp? will be pretty heavy for maybe not enough gain
		}
		*/
	}
}