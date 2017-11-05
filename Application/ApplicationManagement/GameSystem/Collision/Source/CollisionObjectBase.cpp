#include "ApplicationManagement/GameSystem/Collision/Headers/CollisionObjectBase.h"

namespace Application
{
	namespace GameSystem
	{
		namespace Collision
		{
			CollisionObjectBase::CollisionObjectBase(SharedPtr<Transform> collisionTransform)
				: /*Subscriber(Ptr to <CollisionManager>),*/  CollisionTransform(collisionTransform)
			{
				SubscribeToCollider();
			}

			CollisionObjectBase::~CollisionObjectBase()
			{
				UnsubscribeFromCollider();
			}

			void CollisionObjectBase::Update(Second dt)
			{
				// this should be used for collision specific updates (such as stretching the collision size to account for potential misses due to large DT steps
			}

			void CollisionObjectBase::SubscribeToCollider()
			{

			}

			void CollisionObjectBase::UnsubscribeFromCollider()
			{

			}
		}
	}
}