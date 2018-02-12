#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Geometric/Headers/Transform.h"

using namespace Core;
using namespace Core::Geometric;

namespace Application
{
	namespace GameSystem
	{
		/*
		NOTE: We are no longer 'subscribing' to the game object manager (or any relevant manager for related systems), but rather will _need_ to be constructed from the system, where it will
		be added automatically. ALSO - deletion will have to also occur within the system

		This is a base class (essentially an interface) to be used for nay object that needs to be tied into generic game-like elements (getting update calls, position information, anything)

		This template should be used for any object that is going to be in the game

		Similar templates should be employed by Collider and Render objects.

		DO NOT DO THE BELOW:
		So, for example, a game object with no collision information, we make a custom object that implements both GameObjectBase and RenderObjectBase (or children of) but NOT ColliderObjectBase

		INSTEAD:
		GameObjects should be the central item that should HAVE a RenderObject and CollisionObject.
		If we do what was written in the above, the update call would get called several times (for game objects, render objects, and collision objects).
		This way, a GameObject CAN have collision and Rendering (but does not need to) and those parts will update independantly.

		Also, collision objects should have events that the game object/parent object can subscribe to for when it gets hit
		*/
		struct GameObjectBase
		{
			GameObjectBase();
			GameObjectBase(SharedPtr<Transform> transform);

			virtual ~GameObjectBase();

			virtual void Update(Second dt);

		protected:
			SharedPtr<Transform> ObjectTransform;
		};
	}
}
