#pragma once

#include "ApplicationManagement/Headers/Component.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

namespace Application
{
	namespace Rendering
	{
		// a recursive struct to hold elements in a scene
		struct Render : Component<Render>
		{
			static Core::Hash ClashHash()
			{
				return Core::HashValue("Render");
			}

			Render(Core::Ptr<EntityBase> entity, RenderObjectManager& renderManager);

			template <typename T, typename ...Ts>
			Core::Ptr<RenderObjectBase> AddRenderObject(Ts ...args)
			{
				Core::Ptr<RenderObjectBase> newRenderObject = RObjectManager.AddRenderObject<T>(Forward<Ts>(args)...);
				
				Push(RenderObjects, newRenderObject);

				return newRenderObject;
			}

			void RemoveRenderObject(Core::Ptr<RenderObjectBase> renderObject);

		private:
			RenderObjectManager& RObjectManager;
			Core::List<Core::Ptr<RenderObjectBase>> RenderObjects;
		};
	}
}