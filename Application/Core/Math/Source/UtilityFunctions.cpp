#pragma once

#include "Core/Math/Headers/UtilityFunctions.h"

namespace Core
{
	namespace Math
	{
		FQuaternion LerpQuat(FQuaternion a, FQuaternion b, float p)
		{
			FQuaternion lerpedQuaternion;

			lerpedQuaternion.W = Lerp(a.W, b.W, p);
			lerpedQuaternion.X = Lerp(a.X, b.X, p);
			lerpedQuaternion.Y = Lerp(a.Y, b.Y, p);
			lerpedQuaternion.Z = Lerp(a.Z, b.Z, p);

			return lerpedQuaternion;
		}
	}
}