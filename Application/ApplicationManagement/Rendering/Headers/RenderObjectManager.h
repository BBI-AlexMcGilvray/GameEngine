#pragma once

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

namespace Application
{
	namespace Rendering
	{
		struct RenderManager;

		// holds all render objects, handles updating them and passing them in to be rendered
		struct RenderObjectManager
		{
			RenderObjectManager(Core::Ptr<RenderManager> manager);

			void Initialize();
			void Start();

			void Update(Core::Second dt);
			void Render(const Core::Math::Float4x4& mvp, const Core::Math::Color& color);

			void End();
			void CleanUp();

			// This should return a RanderObjectPtr that holds a unique ptr to the render object and will remove the object from
			// the manager once deleted
			template <typename T, typename ...Ts>
			Core::Ptr<T> AddRenderObject(Ts&& ...args)
			{
				Core::UniquePtr<RenderObjectBase> newRenderObject = Core::MakeUnique<T>(Manager, Forward<Ts>(args)...);

				return static_cast<Ptr<T>>(AddRenderObject(move(newRenderObject)));
			}

			virtual Core::Ptr<RenderObjectBase> AddRenderObject(Core::UniquePtr<RenderObjectBase> renderObject);
			virtual void RemoveRenderObject(Core::Ptr<RenderObjectBase> renderObject);

		private:
			// ideally we find a way to make this not a raw pointer, but it should be fine for now since this object
			// will only exist within a render manager, so lifetime is not a concern
			Core::Ptr<RenderManager> Manager;

			Core::List<Core::UniquePtr<RenderObjectBase>> RenderObjects;
		};
	}
}