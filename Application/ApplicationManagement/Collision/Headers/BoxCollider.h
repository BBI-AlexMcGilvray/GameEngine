#pragma once

#include "ApplicationManagement\Collision\Headers\ColliderBase.h"

namespace Application
{
	namespace GameSystem
	{
		namespace Collision
		{
			struct BoxCollider : ColliderBase
			{
				ColliderType GetColliderType() const override
				{
					return ColliderType::Box;
				}

				Float3 Minimum;
				Float3 Maximum;

				BoxCollider(SharedPtr<const Transform> collisionTransform, Float3 dimensions = 1.0f);
				BoxCollider(SharedPtr<const Transform> collisionTransform, Float3 minimum = -0.5f, Float3 maximum = 0.5f);

				float GetBoundingRadius() const override;
				Float3 GetDimensions();

				void SetDimensions(Float3 dimensions);
			};
		}
	}
}