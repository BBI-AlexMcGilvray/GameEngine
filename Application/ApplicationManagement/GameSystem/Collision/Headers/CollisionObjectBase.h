#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Geometric/Headers/Transform.h"
#include "Core/Functionality/Headers/Subscription.h"

using namespace Core;
using namespace Core::Geometric;
using namespace Core::Functionality;

namespace Application
{
	namespace GameSystem
	{
		namespace Collision
		{
			struct CollisionObjectBase : Subscriber
			{
				/*
				This is an INTERFACE to be used by any object that needs collision.

				This template will handle holding onto collision information, subscribing to the collision manager to be rendered, and updating

				This template should be inherited from to produce specific collision requirements (ex: sphere vs box)

				Similar templates should be employed by Renderer and Game objects.

				So, for example, a game object with no collision information, we make a custom object that implements both GameObjectBase and RenderObjectBase (or children of) but NOT ColliderObjectBase
				*/
				CollisionObjectBase(SharedPtr<Transform> collisionTransform);
				virtual ~CollisionObjectBase();

				virtual void Update(Second dt);

			private:
				// this is private because it should never be changed by the render object - it simply reads the transform (same for colliders, but game objects will be able to modify their transform)
				SharedPtr<Transform> CollisionTransform;

				void SubscribeToCollider();
				void UnsubscribeFromCollider();
			};
		}
	}
}