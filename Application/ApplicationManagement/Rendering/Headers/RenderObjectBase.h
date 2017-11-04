#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Geometric/Headers/Transform.h"

using namespace Core;
using namespace Core::Geometric;

namespace Application
{
	namespace Rendering
	{
		/*
			This is a TEMPLATE to be used by any object that needs rendering.

			This template will handle holding onto render information, subscribing to the renderer to be rendered, and updating

			This template should be inherited from to produce specific rendering requirements (ex: UI vs world rendering)

			Similar templates should be employed by Collider and Game objects.

			So, for example, a game object with no collision information, we make a custom object that implements both GameObjectBase and RenderObjectBase (or children of) but NOT ColliderObjectBase
		*/
		struct RenderObjectBase
		{
			RenderObjectBase(SharedPtr<Transform> renderTransform);
			virtual ~RenderObjectBase();

			virtual void Update(Second dt);

		private:
			// this is private because it should never be changed by the render object - it simply reads the transform (same for colliders, but game objects will be able to modify their transform)
			SharedPtr<Transform> RenderTransform;

			void SubscribeToRenderer();
			void UnsubscribeFromRenderer();
		};
	}
}
