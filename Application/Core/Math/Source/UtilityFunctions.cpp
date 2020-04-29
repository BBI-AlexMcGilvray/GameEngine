#pragma once

#include "Core/Math/Headers/UtilityFunctions.h"

namespace Core
{
	namespace Math
	{
		// Simpler, but could potentially use slerp if more precision is required: https://en.wikipedia.org/wiki/Slerp
		FQuaternion LerpQuat(FQuaternion a, FQuaternion b, float p)
		{
			FQuaternion lerpedQuaternion;

			lerpedQuaternion.W = Lerp(a.W, b.W, p);
			lerpedQuaternion.X = Lerp(a.X, b.X, p);
			lerpedQuaternion.Y = Lerp(a.Y, b.Y, p);
			lerpedQuaternion.Z = Lerp(a.Z, b.Z, p);

			lerpedQuaternion = Normalize(lerpedQuaternion);

			return lerpedQuaternion;
		}
	}
}