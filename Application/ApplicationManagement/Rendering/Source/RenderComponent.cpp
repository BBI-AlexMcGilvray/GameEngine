#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		Render::Render(Core::Ptr<EntityBase> entity, RenderObjectManager& renderManager)
			: Component<Render>(entity, this)
			, RObjectManager(renderManager)
		{

		}

		Ptr<RenderObjectBase> Render::AddRenderObject(Ptr<RenderObjectBase> renderObject)
		{
			Push(RenderObjects, move(renderObject));

			return RenderObjects[RenderObjects.size() - 1];
		}

		void Render::RemoveRenderObject(Core::Ptr<RenderObjectBase> renderObject)
		{
			RObjectManager.RemoveRenderObject(renderObject);
		}
	}
}