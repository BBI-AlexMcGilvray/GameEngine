#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Functionality/Headers/Event.h"

#include "Core/Geometric/Headers/Transform.h"

#include "Core/Math/Headers/Color.h"

namespace Application
{
	namespace Rendering
	{
		struct RenderManager;

		/*
			This is an INTERFACE to be used by any object that needs rendering.

			This template will handle holding onto render information, subscribing to the renderer to be rendered, and updating

			This template should be inherited from to produce specific rendering requirements (ex: UI vs world rendering)

			Similar templates should be employed by Collider and Game objects.

			So, for example, a game object with no collision information, we make a custom object that implements both GameObjectBase and RenderObjectBase (or children of) but NOT ColliderObjectBase

			NOTE: These should be created (potentially?) directly in the RenderObjectManager as a UniquePtr! This should also be followed by the Collision and GameSystem groups.
			Because the transform is a SharedPtr, we should still be able to local-space relative to nodes by passing down the changes through the node chain
		*/
		struct RenderObjectBase
		{
			Core::Functionality::Event<> Delete;

			Core::Math::Color ObjectColor;

			RenderObjectBase(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Core::Math::Color color = Core::Math::Color(1.0f, 1.0f, 1.0f, 1.0f));
			virtual ~RenderObjectBase();

			virtual void Update(Core::Second dt);
			void Render(Core::Ptr<RenderManager> manager, const Core::Math::Float4x4& mvp, const Core::Math::Color& color) const;

			virtual Core::size GetVertexCount() const = 0;

		protected:
			Core::Ptr<RenderManager> Manager;
			// this is private because it should never be changed by the render object - it simply reads the transform (same for colliders, but game objects will be able to modify their transform)
			Core::Ptr<Core::Geometric::Transform> RenderTransform;

			virtual void Prepare(const Core::Math::Float4x4& mvp, const Core::Math::Color& color) const = 0;
			virtual void Draw(Core::Ptr<RenderManager> manager) const;
			virtual void CleanUp() const = 0;
		};
	}
}
