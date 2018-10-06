#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

using namespace Core;
using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		struct RenderManager;
		struct RenderObjectBase;

		// holds all render objects, handles updating them and passing them in to be rendered
		struct RenderObjectManager
		{
			RenderObjectManager(Ptr<RenderManager> manager);

			void Initialize();
			void Start();

			void Update(Second dt);
			void Render(const Float4x4& mvp, const Color& color);

			void End();
			void CleanUp();

			// This should return a RanderObjectPtr that holds a unique ptr to the render object and will remove the object from
			// the manager once deleted
			template <typename T, typename ...Ts>
			SharedPtr<T> AddRenderObject(Ts ...args)
			{
				SharedPtr<T> newRenderObject = MakeShared<T>(*Manager, Forward<Ts>(args)...);

				AddRenderObject(newRenderObject);

				return newRenderObject;
			}

			virtual void AddRenderObject(SharedPtr<RenderObjectBase> renderObject);
			virtual void RemoveRenderObject(SharedPtr<RenderObjectBase> renderObject);

		private:
			// ideally we find a way to make this not a raw pointer, but it should be fine for now since this object
			// will only exist within a render manager, so lifetime is not a concern
			Ptr<RenderManager> Manager;

			List<SharedPtr<RenderObjectBase>> RenderObjects;
		};
	}
}