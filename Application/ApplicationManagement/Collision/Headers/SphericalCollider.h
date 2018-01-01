#pragma once

#include "ApplicationManagement\Collision\Headers\CollisionObjectBase.h"

namespace Application
{
	namespace GameSystem
	{
		namespace Collision
		{
			struct SphericalCollider : CollisionObjectBase
			{
				float Radius;
				Float3 Coefficients;

				SphericalCollider(SharedPtr<const Transform> collisionTransform, float radius = 1.0f, Float3 coefficients = 1.0f);

				float GetBoundingRadius() override;

				void SetCoefficients(Float3 coefficients);
			};
		}
	}
}