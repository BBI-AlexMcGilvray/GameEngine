#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Geometric/Headers/Transform.h"
#include "Core/Functionality/Headers/Subscription.h"

#include "ApplicationManagement/Rendering/Headers/RenderManager.h"
#include "ApplicationManagement/Rendering/Shaders/Headers/ObjectShaderBase.h"

using namespace Core;
using namespace Core::Geometric;
using namespace Core::Functionality;

namespace Application
{
	namespace Rendering
	{
		/*
			This is an INTERFACE to be used by any object that needs rendering.

			This template will handle holding onto render information, subscribing to the renderer to be rendered, and updating

			This template should be inherited from to produce specific rendering requirements (ex: UI vs world rendering)

			Similar templates should be employed by Collider and Game objects.

			So, for example, a game object with no collision information, we make a custom object that implements both GameObjectBase and RenderObjectBase (or children of) but NOT ColliderObjectBase
		*/
		struct RenderObjectBase : Subscriber
		{
			RenderObjectBase(RenderManager& manager, Ptr<ObjectShaderBase> objectShader, SharedPtr<Transform> renderTransform);
			virtual ~RenderObjectBase();

			virtual void Update(Second dt);

			void Receive() override;
			virtual void Render();

			virtual uint GetVertexCount() = 0;

		private:
			RenderManager& Manager;
			// this is private because it should never be changed by the render object - it simply reads the transform (same for colliders, but game objects will be able to modify their transform)
			SharedPtr<Transform> RenderTransform;
			Ptr<ObjectShaderBase> ObjectShader;

			virtual void Prepare();
			virtual void Draw();
			virtual void CleanUp();
		};
	}
}
