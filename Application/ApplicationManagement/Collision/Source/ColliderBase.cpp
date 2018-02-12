#include "ApplicationManagement/Collision/Headers/ColliderBase.h"

namespace Application
{
	namespace GameSystem
	{
		namespace Collision
		{
			ColliderBase::ColliderBase(SharedPtr<const Transform> collisionTransform)
				: CollisionTransform(collisionTransform)
			{

			}

			ColliderBase::~ColliderBase()
			{

			}

			void ColliderBase::Update(Second dt)
			{
				// this should be used for collision specific updates (such as stretching the collision size to account for potential misses due to large DT steps
			}
			
			void ColliderBase::OnCollision(SharedPtr<const CollisionBase> collision)
			{
				if (!IsTrigger)
				{
					Collision(collision);
				}
				else
				{
					Trigger(collision);
				}

				return;
			}
		}
	}
}