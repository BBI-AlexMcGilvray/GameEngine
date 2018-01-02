#include "ApplicationManagement/Collision/Headers/SphericalCollider.h"

namespace Application
{
	namespace GameSystem
	{
		namespace Collision
		{
			SphericalCollider::SphericalCollider(SharedPtr<const Transform> collisionTransform, float radius, Float3 coefficients)
				: ColliderBase(collisionTransform), Radius(radius), Coefficients(coefficients)
			{}

			float SphericalCollider::GetBoundingRadius() const
			{
				return Radius;
			}

			void SphericalCollider::SetCoefficients(Float3 coefficients)
			{
				Coefficients = coefficients;
			}
		}
	}
}