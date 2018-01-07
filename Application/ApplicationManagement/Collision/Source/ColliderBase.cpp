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
				SubscribeToCollider();
			}

			ColliderBase::~ColliderBase()
			{
				UnsubscribeFromCollider();
			}

			void ColliderBase::Update(Second dt)
			{
				// this should be used for collision specific updates (such as stretching the collision size to account for potential misses due to large DT steps
			}
			
			void ColliderBase::OnCollision(SharedPtr<const ColliderBase> collider, Float3 location)
			{
				// do nothing
				return;
			}

			void ColliderBase::SubscribeToCollider()
			{

			}

			void ColliderBase::UnsubscribeFromCollider()
			{

			}
		}
	}
}