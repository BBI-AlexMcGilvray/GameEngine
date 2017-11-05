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
		/*
		This is a base class (essentially an interface) to be used for nay object that needs to be tied into generic game-like elements (getting update calls, position information, anything)

		This template should be used for any object that is going to be in the game

		Similar templates should be employed by Collider and Render objects.

		So, for example, a game object with no collision information, we make a custom object that implements both GameObjectBase and RenderObjectBase (or children of) but NOT ColliderObjectBase
		*/
		struct GameObjectBase : Subscriber
		{
			GameObjectBase();
			virtual ~GameObjectBase();

			virtual void Update(Second dt);

		private:
			SharedPtr<Transform> ObjectTransform;

			void SubscribeToGameManager();
			void UnsubscribeFromGameManager();
		};
	}
}
