#pragma once

#include "ApplicationManagement/Headers/Component.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectManager.h"

namespace Application
{
	namespace Rendering
	{
		struct RenderObjectManager;
		struct RenderObjectBase;

		// a struct to hold all render objects of an entity
		struct Render : Component<Render>
		{
			static Core::Hash ClassHash()
			{
				return Core::HashValue("Render");
			}

			Render(Core::Ptr<EntityBase> entity, Core::Ptr<RenderObjectManager> renderManager);

			template <typename T, typename ...Ts>
			Core::Ptr<RenderObjectBase> AddRenderObject(Ts ...args)
			{
				return AddRenderObject(RObjectManager->AddRenderObject<T>(Forward<Ts>(args)...));
			}

			Core::Ptr<RenderObjectBase> AddRenderObject(Core::UniquePtr<RenderObjectBase> renderObject);

			Core::Ptr<RenderObjectBase> AddRenderObject(Core::Ptr<RenderObjectBase> renderObject);

			void RemoveRenderObject(Core::Ptr<RenderObjectBase> renderObject);

		private:
			Core::Ptr<RenderObjectManager> RObjectManager;
			Core::List<Core::Ptr<RenderObjectBase>> RenderObjects;
		};
	}
}